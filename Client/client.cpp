//
// Created by erwan on 10/6/23.
//

#include "client.h"
#include "Elements/Image.h"
#include "Scenes/Background.h"
#include "Scenes/Login.h"
#include "net_message.h"

void client::start()
{
    if (!_build) {
        build();
    }
    while (_engine.isOpen()) {
        _engine.update();
        _bg->update();
    }
}

void client::build()
{
    std::cout << "[CLIENT] Building resources..." << std::endl;
    _engine.init();
    _window = _engine.createEntity();
    _window->addComponent(new Haze::Window(800, 600));

    _bg = std::make_unique<Background>(_engine);
    _bg->build();

    _login = std::make_unique<Login>(_engine);
    _login->build();

    //    _login = std::make_unique<element::Login>(_engine, 100, 300, [this](const std::string &ip, uint16_t port) {
    //        std::cout << "Ip: " << ip << ":" << port << std::endl;
    //        connect(ip, port); });
    //
    //    _startButton = std::make_unique<element::Button>(_engine, "Start Game", [this](int id) {
    //        network::message<protocol::lobby> msg(protocol::lobby::start_room);
    //        send(msg); });
    //    _startButton->getEntity().addComponent(new Haze::Hide);
    //    _startButton->getEntity().addComponent(new Haze::Position(200, 200));

    _build = true;
    std::cout << "[CLIENT] Build completed!" << std::endl;
}

//// TCP Events
//while (!getIncoming().empty()) {
//    network::message<lobby> msg = getIncoming().pop_front().content;
//    switch (msg.header.id) {
//        case lobby::data_channel: {
//            if (!_spectator) {
//                asio::ip::udp::endpoint peer;
//                msg >> peer;
//                peer = udp::endpoint(asio::ip::make_address(_login->getIp()), peer.port());
//                std::cout << "[PEER]: " << peer << std::endl;
//                _spectator = std::make_unique<spectator>(_context, _engine);
//                _spectator->addPeer(peer);
//                _startButton->getEntity().addComponent(new Haze::Hide);
//
//                network::datagram<protocol::data> data(protocol::data::join);
//                _spectator->sendTo(data, peer);
//
//                std::cout << "send join" << std::endl;
//            }
//            break;
//        }
//    }
//}


//if (_spectator) {
//    //            std::cout << "[INBOX] " << _game->getIncoming().count() << std::endl;
//    _spectator->update(50, false);
//    if (_spectator->aliveCD.IsReady()) {
//        _spectator->aliveCD.Activate();
//        _spectator->sendAll(network::datagram<protocol::data>(protocol::data::alive));
//        std::cout << "[GAME] sent Alive" << std::endl;
//    }
//}
