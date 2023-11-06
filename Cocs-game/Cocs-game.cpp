/*
** EPITECH PROJECT, 2023
** cpp r-type
** File description:
** Cocs-game.cpp
*/

#include "Cocs-game.hpp"


Cocs_game::Cocs_game(asio::io_context &context)
: _channel(context), _engine(60)
{
    std::srand(std::time(0));
    _engine.init();
    _engine.setInfoInputs({std::vector<Haze::InputType>(), std::vector<Haze::InputType>(), Haze::MouseType::NOTHING, 0, 0}, 0);
    _engine.setInfoInputs({std::vector<Haze::InputType>(), std::vector<Haze::InputType>(), Haze::MouseType::NOTHING, 0, 0}, 1);
    _engine.setInfoInputs({std::vector<Haze::InputType>(), std::vector<Haze::InputType>(), Haze::MouseType::NOTHING, 0, 0}, 2);
}

uint32_t Cocs_game::getPlayerID(const udp::endpoint &endpoint)
{
    for (auto &player: _players) {
        if (player->_remote && player->_remote->endpoint == endpoint) {
            return player->_id;
        }
    }
    return 0;
}

Cocs_game::~Cocs_game()
{
}

void Cocs_game::sendUpdate()
{
    if (_ball->_entity)
        _ball->sendUpdate();
}

void Cocs_game::update()
{
    for (auto &player: _players) {
        if (player->_entity)
            player->update();
    }
    if (_ball->_entity) {
        int player = _ball->update();
        if (player == 1) {
            _players[0]->changeScore();
        } else if (player == 2) {
            _players[1]->changeScore();
        }
    }
}

void Cocs_game::stop()
{
    _running = false;
}

void Cocs_game::sendEverything(udp::endpoint &to)
{
    for (auto &player: _players) {
        if (player->_entity) {
            player->send();
        }
    }
    if (_ball->_entity)
        _ball->send();
}

void Cocs_game::checkInactiveClients()
{
    for (auto &player: _players) {
        if (player->_remote && player->_remote->activityCd.IsReady()) {
            player->_remote = nullptr;
        }
    }
}

void Cocs_game::onReceive(udp::endpoint from, network::datagram<protocol::data> content)
{
    // refresh player's activity
    for (auto &player: _players) {
        if (player->_remote && player->_remote->endpoint == from)
            player->_remote->activityCd.Activate();
    }

    // process datagram
    switch (content.header.id) {
        case protocol::data::join: {
            for (auto &player: _players) {
                if (!player->_remote) {
                    player->_remote = std::make_unique<Player::Remote>(from);
                    _channel.getGroup().insert(from);
                    sendEverything(from);
                }
            }
            if (_players.size() < 2) {
                _channel.getGroup().insert(from);
                sendEverything(from);
                _players.emplace_back(std::make_unique<Player>(_engine, _channel, _players.size() + 1));
                _players.back()->_remote = std::make_unique<Player::Remote>(from);
                _players.back()->build();
            }
            return;
        }

        case protocol::data::input: {
            Haze::info_inputs_weak info{};
            std::memcpy(&info, content.body.data(), content.header.size);
            //            printInfoInputs(info);

            Haze::info_inputs inputs;
            for (auto &key: info.pressedInputs) {
                if (key != Haze::NO) {
                    inputs.inputsPressed.push_back(key);
                }
            }
            for (auto &key: info.releasedInputs) {
                if (key != Haze::NO) {
                    inputs.inputsReleased.push_back(key);
                }
            }
            inputs.mouseType = info.mouseType;
            inputs.x = info.x;
            inputs.y = info.y;

            uint32_t id = getPlayerID(from);
            if (!id) return;
            std::cout << "Registered inputs from player " << id << std::endl;
            Haze::info_inputs playerInputs = _engine.getInfoInputs()->at(id);
            inputs.inputsPressed.insert(inputs.inputsPressed.end(), playerInputs.inputsPressed.begin(), playerInputs.inputsPressed.end());
            inputs.inputsReleased.insert(inputs.inputsReleased.end(), playerInputs.inputsReleased.begin(), playerInputs.inputsReleased.end());
            _engine.setInfoInputs(inputs, id);
            break;
        }
        default: {
            break;
        }
    }
}

void Cocs_game::createMap()
{
    _ball = std::make_unique<Ball>(_engine, _channel);
    _ball->build();
}

void Cocs_game::start()
{
    _running = true;

    createMap(); // todo jeu


    /**
      * Update Cycle
      */
    while (_running) {
        // Process messages
        size_t count = 0;
        while (count < 5 && !_channel.getIncoming().empty()) {
            auto msg = _channel.getIncoming().pop_front();
            onReceive(msg.target, msg.data);
            count++;
        }
        checkInactiveClients();

        // Process the input received
        _engine.update();

        // Update the state of the non player entity
        update();

        // Send all entities update to clients
        sendUpdate();
    }
}

asio::ip::udp::endpoint Cocs_game::getEndpoint() const
{
    return _channel.getEndpoint();
}
