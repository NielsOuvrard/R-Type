//
// Created by erwan on 10/6/23.
//

#include "client.h"
#include "net_message.h"

client::client() {
    _engine.init();
}

client::~client() {}


void client::start() {
    if (!_isBuild) build();
    while (_engine.isOpen()) {
        if (!_login->isHidden() && isConnected()) {
            _startButton->getEntity().removeComponent("Hide");
            _login->setHide(true);
        }
        if (!_inGame && _dataChannel) {
            _startButton->getEntity().removeComponent("Hide");
        }
        if (_inGame && _dataChannel) {
            _dataChannel->update(5, false);
        }
        _engine.update();
    }
    std::cout << "engine closed!" << std::endl;
}

void client::build() {
    std::cout << "[CLIENT] Building resources..." << std::endl;
    _window = _engine.createEntity();
    _window->addComponent(new Haze::Window(800, 600));

    _login = std::make_unique<element::Login>(_engine, 100, 300, [this](const std::string &ip, uint16_t port) {
        std::cout << "Ip: " << ip << ":" << port << std::endl;
        connect(ip, port);
    });

    _startButton = std::make_unique<element::Button>(_engine, "Start Game", [this](int id) {
        network::message<protocol::lobby> msg(protocol::lobby::start_room);
        send(msg);
    });
    _startButton->getEntity().addComponent(new Haze::Hide);
    _startButton->getEntity().addComponent(new Haze::Position(200, 200));

    std::cout << "[CLIENT] Building completed!" << std::endl;
    _isBuild = true;
}
