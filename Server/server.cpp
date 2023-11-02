//
// Created by erwan on 10/11/23.
//

#include "server.h"

using namespace protocol;

server::server(uint16_t port)
    : server_interface(port)
{}

void server::onMessage(std::shared_ptr<network::connection<lobby>> from, network::message<lobby> &msg)
{
    network::message res{lobby::ok};
    switch (msg.header.id) {
        case lobby::get_rooms: {
            std::list<std::tuple<uint32_t, uint8_t>> ids;
            for (auto &pair: _rooms) {
                ids.emplace_back(pair.first, pair.second->size());
            }
            for (auto &pair: ids) {
                res << std::get<1>(pair)
                    << std::get<0>(pair);
            }
            res << static_cast<uint32_t>(ids.size());
            break;
        }
        case lobby::get_room: {
            uint32_t room_id = 0;
            msg >> room_id;
            if (_rooms.find(room_id) != _rooms.end() && _rooms[room_id]->isMember(from)) {
                const auto &members = _rooms[room_id]->getMembers();
                for (auto &member: members) {
                    char name[32] = {0};
                    bool owner = std::get<1>(member.second) == Room::privileges::owner;
                    std::strcat(name, std::get<0>(member.second).data());
                    res << owner
                        << name;
                }
                res << static_cast<uint32_t>(members.size());
            } else {
                res.header.id = lobby::ko;
            }
            break;
        }
        case lobby::get_chats: {
            uint32_t room_id = 0;
            msg >> room_id;
            if (_rooms[room_id]->isMember(from)) {
                auto chats = _rooms[room_id]->getChats();
                for (auto &chat: chats) {
                    msg << chat.sender.data() << chat.content.data();
                }
                msg << static_cast<uint32_t>(chats.size());
            } else {
                res.header.id = lobby::ko;
            }
        }
        case lobby::join_room: {
            uint32_t room_id = 0;
            char nickname[32] = {0};
            msg >> room_id >> nickname;
            if (_rooms.find(room_id) != _rooms.end() && _rooms[room_id]->isOpen() && !_rooms[room_id]->isFull()) {
                _rooms[room_id]->addConnection(from, nickname);
            } else {
                res.header.id = lobby::ko;
            }
            break;
        }
        case lobby::create_room: {
            char nickname[32] = {0};
            msg >> nickname;
            _rooms[_idCounter] = std::make_unique<Room>();
            _rooms[_idCounter]->addConnection(from, nickname, Room::privileges::owner);
            res << _idCounter;
            _idCounter++;
            break;
        }
        case lobby::start_room: {
            uint32_t room_id = 0;
            msg >> room_id;
            if (_rooms[room_id]->isOpen() && _rooms[room_id]->canStart(from)) {
                // TODO: Start thread and send datachannel
            }
            messageAllClient(res);
            return;
        }
        case lobby::leave_room: {
            uint32_t room_id = 0;
            msg >> room_id;
            if (!_rooms[room_id]->disconnect(from)) {
                msg.header.id = lobby::ko;
            };
            break;
        }
        default: {
            break;
        }
    }
    messageClient(from, res);
}

bool server::onClientConnection(std::shared_ptr<network::connection<lobby>> client)
{
    return true;
}

void server::onClientDisconnect(std::shared_ptr<network::connection<lobby>> client)
{
    for (auto &pair: _rooms) {
        if (pair.second->disconnect(client)) { break; }
    }
}
