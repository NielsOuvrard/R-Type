//
// Created by erwan on 10/6/23.
//

#include "client.h"
#include "Elements/Image.h"
#include "Scenes/Background.h"
#include "Scenes/LobbyItem.h"
#include "Scenes/LobbyList.h"
#include "Scenes/Login.h"
#include "net_message.h"

namespace net = network;

void client::start()
{
    if (!_build) {
        build();
    }
    while (_engine.isOpen()) {
        _engine.update();

        emit();
        receive();

        for (auto &[name, element]: _elements) {
            if (!element->getHide()) {
                element->update();
            }
        }
    }
}

void client::build()
{
    std::cout << "[CLIENT] Building resources..." << std::endl;
    _engine.init();
    _window = _engine.createEntity();
    _window->addComponent(new Haze::Window(800, 600));

    _elements["bg"] = std::make_shared<Background>(_engine);
    _elements["bg"]->build();

    _elements["login"] = std::make_shared<Login>(_engine, [this]() {
        auto name = _elements["login"]->get<TextInput>("name")->getValue();
        auto ip = _elements["login"]->get<TextInput>("ip")->getValue();
        auto port = _elements["login"]->get<TextInput>("port")->getValue();
        if (name.empty() || ip.empty() || port.empty()) return;
        connect(ip, static_cast<uint16_t>(std::stoul(port)));
        _elements["login"]->setHide(true);
        _elements["lobbyList"]->setHide(false);
        _selected = "lobbyList";
    });
    _elements["login"]->build();
    _elements["login"]->get<TextInput>("name")->setValue("Toto");
    _elements["login"]->get<TextInput>("ip")->setValue("127.0.0.1");
    _elements["login"]->get<TextInput>("port")->setValue("3030");

    _elements["lobbyList"] = std::make_shared<LobbyList>(
            _engine,
            _currentLobby,
            [this]() {
                if (_state != state::ok) return;
                std::cout << "Join" << std::endl;
                char name[32] = {0};
                std::strncpy(name, _elements["login"]->get<TextInput>("name")->getValue().data(), 32);
                net::message<lobby> msg(lobby::join_room);
                auto l = std::dynamic_pointer_cast<LobbyList>(_elements["lobbyList"]);
                msg << name << _currentLobby;
                send(msg);
                _state = state::w_join;
            },
            [this]() {
                if (_state != state::ok) return;
                std::cout << "Create" << std::endl;
                char name[32] = {0};
                std::strncpy(name, _elements["login"]->get<TextInput>("name")->getValue().data(), 32);
                net::message<lobby> msg(lobby::create_room);
                msg << name;
                send(msg);
                _state = state::w_cr_room;
            },
            [this]() {
                std::cout << "Disconnect" << std::endl;
            });
    _elements["lobbyList"]->build();
    _elements["lobbyList"]->setHide(true);

    _selected = "login";
    _build = true;
    std::cout << "[CLIENT] Build completed!" << std::endl;
}

void client::receive()
{
    while (!getIncoming().empty()) {
        network::message<lobby> msg = getIncoming().pop_front().content;
        switch (msg.header.id) {
            case lobby::ok: {
                handleOk(msg);
                break;
            }
        }
    }
}

void client::emit()
{
    static Cooldown getRoomsCD(2s);
    static Cooldown getRoomCD(2s);

    if (_selected == "lobbyList" && _state == state::ok && getRoomsCD.IsReady()) {
        //        std::cout << "[EMIT] get all rooms" << std::endl;
        net::message<lobby> msg(lobby::get_rooms);
        send(msg);
        _state = state::w_rooms;
        getRoomsCD.Activate();

    } else if (_selected == "lobby" && _state == state::ok && getRoomCD.IsReady()) {
        //        std::cout << "[EMIT] get single room" << std::endl;
        net::message<lobby> msg(lobby::get_room);
        msg << _currentLobby;
        send(msg);
        _state = state::w_rooms;
        getRoomCD.Activate();
    }
}

void client::handleOk(network::message<lobby> &msg)
{
    switch (_state) {
        case state::w_cr_room: {
            msg >> _currentLobby;
            _elements["lobbyList"]->setHide(true);
            _selected = "lobby";
            _state = state::ok;
            std::cout << "Room #" << _currentLobby << " created" << std::endl;
            break;
        }
        case state::w_rooms: {
            auto listElem = std::dynamic_pointer_cast<LobbyList>(_elements["lobbyList"]);
            auto &items = listElem->_items;
            uint32_t nbRooms = 0, id = 0;
            uint8_t nbLeft = 0;

            // flag all keys to dead
            for (auto &[key, val]: items) {
                val->dead = true;
            }

            // create or update all items
            msg >> nbRooms;
            while (nbRooms--) {
                msg >> id >> nbLeft;
                if (items[id]) {
                    items[id]->_nbLeft = nbLeft;
                    items[id]->dead = false;
                } else {
                    //                    std::cout << "Created new lobby #" << id << std::endl;
                    items[id] = std::make_unique<LobbyItem>(_engine, id, 4, nbLeft, [this](uint32_t id) {
                        _currentLobby = id;
                    });
                    items[id]->build();
                    items[id]->setHide(true);
                }
            }

            // Removes all dead rooms
            auto it = items.begin();
            while (it != items.end()) {
                if (it->second->dead) {
                    if (_currentLobby == it->first) {
                        it = items.erase(it);
                        _currentLobby = it->first;
                    } else {
                        it = items.erase(it);
                    }
                } else {
                    it++;
                }
            }

            _state = state::ok;
            //            std::cout << "Rooms received" << std::endl;
            break;
        }
        case state::w_join: {
            _elements["lobbyList"]->setHide(true);
            _selected = "lobby";
            _state = state::ok;
            break;
        }
    }
}
