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
    : _channel(context)
{
    _engine.init();
    _engine.setInfoInputs({std::vector<Haze::InputType>(), std::vector<Haze::InputType>(), Haze::MouseType::NOTHING, 0, 0}, 0);
    _engine.setInfoInputs({std::vector<Haze::InputType>(), std::vector<Haze::InputType>(), Haze::MouseType::NOTHING, 0, 0}, 1);
    _engine.setInfoInputs({std::vector<Haze::InputType>(), std::vector<Haze::InputType>(), Haze::MouseType::NOTHING, 0, 0}, 2);
    _engine.setInfoInputs({std::vector<Haze::InputType>(), std::vector<Haze::InputType>(), Haze::MouseType::NOTHING, 0, 0}, 3);
    _engine.setInfoInputs({std::vector<Haze::InputType>(), std::vector<Haze::InputType>(), Haze::MouseType::NOTHING, 0, 0}, 4);

    _background = std::make_unique<Paralax>(_engine, _channel);
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
            if (missile->_entity) {// <-- here
                missile->send();
            }
        }
    }
    for (auto &enemy: _enemies) {
        if (enemy->_entity) {
            enemy->send();
        }
        for (auto &missile: enemy->_missiles) {
            if (missile->_entity) {// <-- here
                missile->send();
            }
        }
    }
}

void Rtype::start()
{
    _running = true;
    std::chrono::steady_clock::time_point previousTime = std::chrono::steady_clock::now();
    const std::chrono::milliseconds targetFrameTime(1000 / 60);// 60 FPS

    _background->build();

    std::ifstream inputFile("assets/AnimationJSON/ground.json");
    nlohmann::json jsonData;

    if (!inputFile.is_open()) {
        std::cerr << "Error: Could not open file for reading" << std::endl;
        return;
    }
    inputFile >> jsonData;
    inputFile.close();

    std::ifstream mapFile("assets/AnimationJSON/map.json");
    nlohmann::json jsonMapData;
    if (!mapFile.is_open()) {
        std::cerr << "Error: Could not open map for reading" << std::endl;
        return;
    }
    mapFile >> jsonMapData;
    mapFile.close();

    std::cout << "Open map\n";
    nlohmann::json map_tiles = jsonMapData["map"];
    uint16_t i = 0;
    for (const auto &tile: map_tiles) {
        _walls.emplace_back(std::make_unique<Wall>(_engine, _channel, jsonData, (48 * 3) * i, 0, false));
        _walls.back()->build(tile["tile_top"]);
        _walls.emplace_back(std::make_unique<Wall>(_engine, _channel, jsonData, (48 * 3) * i, 600, true));
        _walls.back()->build(tile["tile_bottom"]);
        i++;
    }
    std::cout << "Map Opened\n";

    _enemies.emplace_back(std::make_unique<Enemy>(_engine, _channel));
    _enemies.back()->build();

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

        // Calculate time taken in this loop
        std::chrono::steady_clock::time_point currentTime = std::chrono::steady_clock::now();
        std::chrono::milliseconds elapsedTime = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - previousTime);

        // Sleep to achieve the target frame rate
        if (elapsedTime < targetFrameTime) {
            std::this_thread::sleep_for(targetFrameTime - elapsedTime);
        }
        previousTime = std::chrono::steady_clock::now();
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
//                    std::cout << "pressed " << char('a' + key - 1) << std::endl;
                }
            }
            for (auto &key: info.releasedInputs) {
                if (key != Haze::NO) {
                    inputs.inputsReleased.push_back(key);
//                    std::cout << "released " << char('a' + key - 1) << std::endl;
                }
            }
            inputs.mouseType = info.mouseType;
            inputs.x = info.x;
            inputs.y = info.y;

            uint32_t id = getPlayerID(from);
            if (!id) return;
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

void Rtype::sendUpdate()
{
    _background->sendUpdate();
    for (auto &player: _players) {
        if (player->_entity) {
            player->sendUpdate();
        }
    }
    _background->sendUpdate();
    for (auto &wall: _walls) {
        wall->sendUpdate();
    }
}

void Rtype::update()
{
    for (auto &Enemy: _enemies)
        Enemy->update();
    for (auto &player: _players) {
        player->update();
    }
    for (auto &enemy: _enemies) {
        enemy->update();
        if (enemy->_entity) {
            enemy->shoot();
        }
    }
    _background->update();
}
