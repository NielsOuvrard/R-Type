/*
** ooooooooo.           ooooooooooooo
** `888   `Y88.         8'   888   `8
**  888   .d88'              888      oooo    ooo oo.ooooo.   .ooooo.
**  888ooo88P'               888       `88.  .8'   888' `88b d88' `88b
**  888`88b.    8888888      888        `88..8'    888   888 888ooo888
**  888  `88b.               888         `888'     888   888 888    .o
** o888o  o888o             o888o         .8'      888bod8P' `Y8bod8P'
**                                    .o..P'       888
**                                    `Y8P'       o888o
**
** R-Type
*/

#include "Rtype.hpp"

Rtype::Rtype(asio::io_context &context)
    : _channel(context), _engine(10),
      _typeEntities{_enemies_type, _explosions_type, _shots_type, _bosses_type},
      _dataGame{_engine, _channel, _background, _boss, _shots, _walls, _players, _explosions, _enemies, _map_moving}
{
    std::srand(std::time(0));
    _engine.init();
    _engine.setInfoInputs({std::vector<Haze::InputType>(), std::vector<Haze::InputType>(), Haze::MouseType::NOTHING, 0, 0}, 0);
    _engine.setInfoInputs({std::vector<Haze::InputType>(), std::vector<Haze::InputType>(), Haze::MouseType::NOTHING, 0, 0}, 1);
    _engine.setInfoInputs({std::vector<Haze::InputType>(), std::vector<Haze::InputType>(), Haze::MouseType::NOTHING, 0, 0}, 2);
    _engine.setInfoInputs({std::vector<Haze::InputType>(), std::vector<Haze::InputType>(), Haze::MouseType::NOTHING, 0, 0}, 3);
    _engine.setInfoInputs({std::vector<Haze::InputType>(), std::vector<Haze::InputType>(), Haze::MouseType::NOTHING, 0, 0}, 4);

    _background = std::make_unique<Parallax>(_dataGame);

    _mapHandler = std::make_unique<Map>(_dataGame, _typeEntities);
    _map_moving = true;
}

Rtype::~Rtype() = default;

void printInfoInputs(const Haze::info_inputs_weak &info)
{
    for (const auto &input: info.pressedInputs) {
        std::cout << static_cast<int>(input) << " ";
    }
    std::cout << std::endl;

    std::cout << "Released Inputs: ";
    for (const auto &input: info.releasedInputs) {
        std::cout << static_cast<int>(input) << " ";
    }
    std::cout << std::endl;

    std::cout << "Mouse Type: " << static_cast<int>(info.mouseType) << std::endl;
    std::cout << "Mouse Coordinates: (" << info.x << ", " << info.y << ")" << std::endl;
}

void Rtype::checkInactiveClients()
{
    for (auto &player: _players) {
        if (player->_remote && player->_remote->activityCd.IsReady()) {
            player->_remote = nullptr;
        }
    }
}

void Rtype::stop()
{
    _running = false;
}

uint32_t Rtype::getPlayerID(const udp::endpoint &endpoint)
{
    for (auto &player: _players) {
        if (player->_remote && player->_remote->endpoint == endpoint) {
            return player->_id;
        }
    }
    return 0;
}

void Rtype::sendEverything(udp::endpoint &to)
{
    _background->send();
    for (auto &wall: _walls) {
        wall->send();
    }

    /**
     * Checking for missiles entity may be useless as it is
     * cleaned up in the player and enemy's update method
     * cf: here
     */
    for (auto &player: _players) {
        if (player->_entity) {
            player->send();
        }
        for (auto &missile: player->_missiles) {
            if (missile->_entity) {
                missile->send();
            }
        }
    }
    for (auto &enemy: _enemies) {
        if (enemy->_entity) {
            enemy->send();
        }
        for (auto &missile: enemy->_missiles) {
            if (missile->_entity) {
                missile->send();
            }
        }
    }
    // TODO add boss
}

void Rtype::start()
{
    _running = true;
    jsonHandler();
    _mapHandler->build();

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
    }
}

void Rtype::onReceive(udp::endpoint from, network::datagram<protocol::data> content)
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
            if (_players.size() < 4) {
                _channel.getGroup().insert(from);
                sendEverything(from);
                _players.emplace_back(std::make_unique<Player>(_dataGame, _typeEntities, _players.size() + 1));
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

asio::ip::udp::endpoint Rtype::getEndpoint() const
{
    return _channel.getEndpoint();
}

void Rtype::update()
{
    /**
     * remove and add wall
     */
    _mapHandler->update();

    if (_boss) {
        _boss->update();
    }
    /**
     * Enemy & Shots' cleanup cycle
     */
    bool enemyToCleanup = false;
    for (auto &enemy: _enemies) {
        // Cleanup unreachable missiles
        enemy->update();
        if (enemy->_isDead) {
            // * create explosion

            _explosions.emplace_back(std::make_unique<Explosion>(_dataGame, _typeEntities, enemy->_data.x, enemy->_data.y, enemy->_data.explosion_type));
            _explosions.back()->build();
            _explosions.back()->send();
            std::cout << "Explosion created" << std::endl;
            enemy->_isDead = false;
        }
        // Cleanup unreachable enemies
        if (enemy->_entity) {
            auto enemyPos = dynamic_cast<Haze::Position *>(enemy->_entity->getComponent("Position"));
            if (enemyPos->x <= -50) {
                _channel.sendGroup(RType::message::deleteEntity(enemy->_entity->getId()));
                enemy->_entity->addComponent(new Haze::Destroy());
                enemy->_entity = nullptr;
            }
        }

        // Cleanup enemy Instance if it contains nothing
        if (!enemy->_entity && enemy->_missiles.empty()) {
            enemy.reset();
            enemyToCleanup = true;
        }
    }
    if (enemyToCleanup)
        _enemies.erase(std::remove(_enemies.begin(), _enemies.end(), nullptr), _enemies.end());

    // Trigger enemy actions
    for (auto &enemy: _enemies) {
        if (enemy->_entity) {
            enemy->shot();
        }
    }
    if (_boss) {
        _boss->shot();
    }

    for (auto &explosion: _explosions) {
        if (explosion->_time_to_destroyCd.IsReady()) {
            explosion->destroy();
            explosion = nullptr;
            std::cout << "explosion->_time_to_destroyCd.IsReady == true\n";
        }
    }
    // * remove explosions null
    _explosions.erase(std::remove_if(_explosions.begin(), _explosions.end(), [](const std::unique_ptr<Explosion> &explosion) {
                          return explosion == nullptr;
                      }),
                      _explosions.end());

    /**
     * Enemy & Shots' cleanup cycle
     */
    bool playerToCleanup = false;
    for (auto &player: _players) {
        // Cleanup unreachable missiles
        player->update();

        // Cleanup player Instance if it contains nothing
        if (!player->_entity && player->_missiles.empty()) {
            player.reset();
            playerToCleanup = true;
        }
    }
    if (playerToCleanup)
        _players.erase(std::remove(_players.begin(), _players.end(), nullptr), _players.end());
}
