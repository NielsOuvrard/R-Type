//
// Created by erwan on 10/6/23.
//

#include "client.h"
#include "Elements/Image.h"
#include "Scenes/Background.h"
#include "Scenes/LobbyList.h"
#include "Scenes/Login.h"
#include "net_message.h"

void client::start()
{
    if (!_build) {
        build();
    }
    while (_engine.isOpen()) {
        _engine.update();

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

    _elements["bg"] = std::make_unique<Background>(_engine);
    _elements["bg"]->build();

    _elements["login"] = std::make_unique<Login>(_engine, [this]() {
        auto name = _elements["login"]->get<TextInput>("name")->getValue();
        auto ip = _elements["login"]->get<TextInput>("ip")->getValue();
        auto port = _elements["login"]->get<TextInput>("port")->getValue();
        if (name.empty() || ip.empty() || port.empty()) return;
        connect(ip, static_cast<uint16_t>(std::stoul(port)));
        _elements["login"]->setHide(true);
        _elements["lobbyList"]->setHide(false);
    });
    _elements["login"]->build();
    _elements["login"]->get<TextInput>("name")->setValue("Toto");
    _elements["login"]->get<TextInput>("ip")->setValue("127.0.0.1");
    _elements["login"]->get<TextInput>("port")->setValue("3030");

    _elements["lobbyList"] = std::make_unique<LobbyList>(
            _engine,
            [this]() {
                std::cout << "Join" << std::endl;
            },
            [this]() {
                std::cout << "Create" << std::endl;
            },
            [this]() {
                std::cout << "Disconnect" << std::endl;
            });
    _elements["lobbyList"]->build();
    _elements["lobbyList"]->setHide(true);

    selected = "login";
    _build = true;
    std::cout << "[CLIENT] Build completed!" << std::endl;
}

void client::receive()
{
    while (!getIncoming().empty()) {
        network::message<lobby> msg = getIncoming().pop_front().content;
        switch (msg.header.id) {
        }
    }
}

void client::send()
{
}
