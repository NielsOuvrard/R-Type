//
// Created by erwan on 10/6/23.
//

#include "client.h"
#include "net_message.h"

client::client()
{
    _engine.init();
}

client::~client() {}

void client::start()
{
    if (!_isBuild)
        build();
    std::chrono::steady_clock::time_point previousTime = std::chrono::steady_clock::now();
    const std::chrono::milliseconds targetFrameTime(1000 / 60);// 60 FPS
    while (_engine.isOpen()) {
        if (!_login->isHidden() && isConnected()) {
            _startButton->getEntity().removeComponent("Hide");
            _login->setHide(true);
        }

        if (_game) {
            //            std::cout << "[INBOX] " << _game->getIncoming().count() << std::endl;
            _game->update(50, false);
            if (_game->aliveCD.IsReady()) {
                _game->aliveCD.Activate();
                _game->sendAll(network::datagram<protocol::data>(protocol::data::alive));
                std::cout << "[GAME] sent Alive" << std::endl;
            }
        }

        // TCP Events
        while (!getIncoming().empty()) {
            network::message<lobby> msg = getIncoming().pop_front().content;
            switch (msg.header.id) {
                case lobby::data_channel: {
                    if (!_game) {
                        asio::ip::udp::endpoint peer;
                        msg >> peer;
                        _game = std::make_unique<game>(_context, _engine);
                        _game->addPeer(peer);
                        _startButton->getEntity().addComponent(new Haze::Hide);

                        network::datagram<protocol::data> data(protocol::data::join);
                        _game->sendTo(data, peer);

                        std::cout << "send join" << std::endl;
                    }
                    break;
                }
            }
        }

        std::vector<Haze::info_inputs> *inputs = _engine.getInfoInputs();

        // if m is pressed, send a message to the server
        if (inputs->size() > 0 && inputs->at(0).inputsPressed.size() > 0 && inputs->at(0).inputsPressed[0] == Haze::InputType::KEY_M) {
            network::datagram<protocol::data> data(protocol::data::join);

            _game->sendAll(data);
            std::cout << "send join" << std::endl;
        }
        _engine.update();

        std::chrono::steady_clock::time_point currentTime = std::chrono::steady_clock::now();
        std::chrono::milliseconds elapsedTime = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - previousTime);
        // Sleep to achieve the target frame rate
        if (elapsedTime < targetFrameTime) {
            std::this_thread::sleep_for(targetFrameTime - elapsedTime);
        }
        previousTime = std::chrono::steady_clock::now();
    }
    std::cout << "engine closed!" << std::endl;
}

void client::build()
{
    std::cout << "[CLIENT] Building resources..." << std::endl;
    _window = _engine.createEntity();
    _window->addComponent(new Haze::Window(800, 600));

    _login = std::make_unique<element::Login>(_engine, 100, 300, [this](const std::string &ip, uint16_t port) {
        std::cout << "Ip: " << ip << ":" << port << std::endl;
        connect(ip, port); });

    _startButton = std::make_unique<element::Button>(_engine, "Start Game", [this](int id) {
        network::message<protocol::lobby> msg(protocol::lobby::start_room);
        send(msg); });
    _startButton->getEntity().addComponent(new Haze::Hide);
    _startButton->getEntity().addComponent(new Haze::Position(200, 200));

    std::cout << "[CLIENT] Building completed!" << std::endl;
    _isBuild = true;
}
