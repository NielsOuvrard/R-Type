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
#include "data.h"
#include "net_data_channel.h"
#include "net_server.h"
#include "protocol.h"

#define IS_KEY_PRESSED(key) (std::find(components.begin(), components.end(), Haze::InputType::key) != components.end())

Rtype::Rtype(asio::io_context &context)
    : network::data_channel<protocol::data>(context),
      _players({Player()})
{
    _engine.init();
    _engine.setInfoInputs({std::vector<Haze::InputType>(), std::vector<Haze::InputType>(), Haze::MouseType::NOTHING, 0, 0}, 0);
    _engine.setInfoInputs({std::vector<Haze::InputType>(), std::vector<Haze::InputType>(), Haze::MouseType::NOTHING, 0, 0}, 1);
    _engine.setInfoInputs({std::vector<Haze::InputType>(), std::vector<Haze::InputType>(), Haze::MouseType::NOTHING, 0, 0}, 2);
    _engine.setInfoInputs({std::vector<Haze::InputType>(), std::vector<Haze::InputType>(), Haze::MouseType::NOTHING, 0, 0}, 3);
    _engine.setInfoInputs({std::vector<Haze::InputType>(), std::vector<Haze::InputType>(), Haze::MouseType::NOTHING, 0, 0}, 4);
}

Rtype::~Rtype() = default;

void Rtype::checkInactiveClients()
{
    for (auto &player: _players) {
        if (player.remote && player.remote->activityCd.IsReady()) {
            std::cout << "[RType] Player " << player.id << " Timeout!" << std::endl;
            player.remote = nullptr;
        }
    }
}

void Rtype::start()
{
    _running = true;
    std::chrono::steady_clock::time_point previousTime = std::chrono::steady_clock::now();
    const std::chrono::milliseconds targetFrameTime(1000 / 60);// 60 FPS

    while (_running) {
        // moveBackground(); // necessary for collision
        _engine.update();
        update(5, false);
        checkInactiveClients();

        for (auto &player: _players) {
            if (player.remote && player.entity) {
                auto pos = dynamic_cast<Haze::Position *>(player.entity->getComponent("Position"));
                auto scale = dynamic_cast<Haze::Scale *>(player.entity->getComponent("Scale"));
                auto hitbox = dynamic_cast<Haze::Hitbox *>(player.entity->getComponent("Hitbox"))->hitbox.front();

                sendAll(RType::message::addComponent(player.entity->getId(), "Position", new Haze::PositionData{pos->x, pos->y}, sizeof(Haze::PositionData)));
                sendAll(RType::message::addComponent(player.entity->getId(), "Scale", new Haze::ScaleData{scale->x, scale->y}, sizeof(Haze::ScaleData)));
                sendAll(RType::message::addComponent(player.entity->getId(), "Hitbox", new Haze::HitboxData{hitbox}, sizeof(Haze::HitboxData)));
            }
        }

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

void Rtype::stop()
{
    _running = false;
}

// TODO: change the return type to a shared_ptr
Player &Rtype::findPlayer(const udp::endpoint &endpoint)
{
    for (auto &player: _players) {
        if (player.remote && player.remote->endpoint == endpoint)
            return player;
    }
}

uint32_t Rtype::findPlayerIndex(const udp::endpoint &endpoint)
{
    uint32_t index = 1;
    for (auto &player: _players) {
        if (player.remote && player.remote->endpoint == endpoint)
            return index;
        index++;
    }
    return 0;
}

void Rtype::sendEverything(udp::endpoint &to)
{
    // * send to the new player all players data
    for (auto &player: _players) {
        if (player.remote && player.entity) {
            std::cout << "\x1B[32m"
                      << "SEND PLAYER " << player.entity->getId() << "\n\x1B[0m";
            auto pos = dynamic_cast<Haze::Position *>(player.entity->getComponent("Position"));
            auto scale = dynamic_cast<Haze::Scale *>(player.entity->getComponent("Scale"));
            auto hitbox = dynamic_cast<Haze::Hitbox *>(player.entity->getComponent("Hitbox"))->hitbox.front();

            sendTo(RType::message::createEntity(player.entity->getId()), to);
            sendTo(RType::message::addComponent(player.entity->getId(), "Position", new Haze::PositionData{pos->x, pos->y}, sizeof(Haze::PositionData)), to);
            sendTo(RType::message::addComponent(player.entity->getId(), "Scale", new Haze::ScaleData{scale->x, scale->y}, sizeof(Haze::ScaleData)), to);
            sendTo(RType::message::addComponent(player.entity->getId(), "Hitbox", new Haze::HitboxData{hitbox}, sizeof(Haze::HitboxData)), to);
            sendTo(RType::message::addComponent(player.entity->getId(), "Sprite", new Haze::SpriteData{"assets/r-typesheet30a.gif"}, sizeof(Haze::SpriteData)), to);
            sendTo(RType::message::addComponent(player.entity->getId(), "HitboxDisplay", nullptr, 0), to);
        }
    }
    // * send to the new player all shots and ennemies

    //    for (const std::string &type: _engine.getEntity(0)) {
    //        if (type == "Window") {
    //            break;
    //        }
    //        auto component = _engine.getComponentList()->getComponent(type, 0);

    // Haze::Component *info;
    //        network::datagram<protocol::data> msg_compo(protocol::data::add_component);
    //
    //        std::memcpy(msg_compo.body.data(), static_cast<void *>(component), sizeof(Haze::Component));
    //        sendTo(msg_compo, to);
    //    }
}

void printInfoInputs(const Haze::info_inputs_weak &info)
{
    std::cout << "Pressed Inputs: ";
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

void Rtype::onReceive(udp::endpoint from, network::datagram<protocol::data> content)
{
    // refresh player's activity
    for (auto &player: _players) {
        if (player.remote && player.remote->endpoint == from)
            player.remote->activityCd.Activate();
    }

    // process datagram
    switch (content.header.id) {
        case protocol::data::join: {
            std::cout << "[SERVER] RECEIVE JOIN\n";
            // * if client is already connected
            for (auto &player: _players) {
                if (player.remote && player.remote->endpoint == from)
                    return;// refuse the connection
            }
            // * if didn't exist
            uint8_t id = 1;
            for (auto &player: _players) {
                if (!player.remote) {
                    player.remote = std::make_unique<Player::Remote>(from);
                    sendEverything(from);
                    if (!player.entity) {
                        player.id = id;
                        createPlayer(player);
                    }
                    return;
                }
                id++;
            }
            // ! Client was refused
            return;
        }

        case protocol::data::input: {
            // std::cout << "\x1B[32m[SERVER] INPUT RECEIVE\n";
            Haze::info_inputs_weak info{};
            std::memcpy(&info, content.body.data(), content.header.size);
            printInfoInputs(info);
            Haze::info_inputs inputs;
            for (auto &key: info.pressedInputs) {
                if (key != Haze::NO) {
                    inputs.inputsPressed.push_back(key);
                    std::cout << "pressed " << char('a' + key) << std::endl;
                }
            }
            for (auto &key: info.releasedInputs) {
                if (key != Haze::NO) {
                    inputs.inputsReleased.push_back(key);
                    std::cout << "released " << char('a' + key) << std::endl;
                }
            }
            inputs.mouseType = info.mouseType;
            inputs.x = info.x;
            inputs.y = info.y;
            //            Haze::InputType keyFound;
            //            std::memcpy(&keyFound, content.body.data(), 1);
            //            Haze::InputType keyReleased;
            //            std::memcpy(&keyReleased, content.body.data() + 1, 1);
            //            Haze::info_inputs inputs{};
            //            inputs.inputsPressed.push_back(keyFound);
            //            inputs.inputsReleased.push_back(keyFound);

            uint32_t id = findPlayerIndex(from);
            if (id == 0)
                return;
            _engine.setInfoInputs(inputs, id);
            break;
        }
        default: {
            break;
        }
    }
}

void Rtype::createPlayer(Player &player)
{
    std::cout << "\x1B[31m"
              << "CREATE PLAYER"
              << "\n\x1B[0m";
    player.entity = player.entity = _engine.createEntity();
    player.entity->addComponent(new Haze::Velocity(0, 0));
    player.entity->addComponent(new Haze::Position(100, 200));
    player.entity->addComponent(new Haze::Scale(3, 3));
    player.entity->addComponent(new Haze::Hitbox({{0, 0, 32, 14}}));

    // TODO: Free allocated Data created with new
    sendAll(RType::message::createEntity(player.entity->getId()));
    sendAll(RType::message::addComponent(player.entity->getId(), "Position", new Haze::PositionData{100, 200}, sizeof(Haze::PositionData)));
    sendAll(RType::message::addComponent(player.entity->getId(), "Scale", new Haze::ScaleData{3, 3}, sizeof(Haze::ScaleData)));
    sendAll(RType::message::addComponent(player.entity->getId(), "Hitbox", new Haze::HitboxData({0, 0, 32, 14}), sizeof(Haze::HitboxData)));
    sendAll(RType::message::addComponent(player.entity->getId(), "HitboxDisplay", nullptr, 0));
    sendAll(RType::message::addComponent(player.entity->getId(), "Sprite", new Haze::SpriteData{"assets/sprites/spaceship.gif"}, sizeof(Haze::SpriteData)));
    sendAll(RType::message::addComponent(player.entity->getId(), "Animation", new Haze::AnimationData{"assets/AnimationJSON/spaceship.json"}, sizeof(Haze::SpriteData)));

    // ! animation didn't work, receive {0, 0, 0, 0}
    //    sendAll(RType::message::addComponent(client.entity->getId(), "Animation", new Haze::AnimationData({
    //        {
    //        {0, 0, 34, 34},
    //        {34, 0, 34, 34},
    //        {68, 0, 34, 34}
    //        },
    //        Haze::Animation::AnimationType::LOOP,
    //        true, 0.2
    //        }), sizeof(Haze::AnimationData)));

    player.entity->addComponent(new Haze::OnKeyPressed(
            [this, &player](int id, std::vector<Haze::InputType> components) {
                if (IS_KEY_PRESSED(KEY_F) && player.missileCd.IsReady()) {
                    player.missileCd.Activate();
                    Haze::Entity *newShot = _engine.createEntity();
                    auto position = dynamic_cast<Haze::Position *>(player.entity->getComponent("Position"));
                    newShot->addComponent(new Haze::Position(position->x + 33 * 3, position->y));
                    newShot->addComponent(new Haze::Velocity(2, 0));
                    newShot->addComponent(new Haze::Scale(3, 3));
                    // TODO add hitbox, collider and send animation...
                    _entities.push_back(newShot);
                    // * send shot
                    sendAll(RType::message::createEntity(newShot->getId()));
                    sendAll(RType::message::addComponent(newShot->getId(), "Position", new Haze::PositionData{position->x + 33 * 3, position->y}, sizeof(Haze::PositionData)));
                    sendAll(RType::message::addComponent(newShot->getId(), "Scale", new Haze::ScaleData{3, 3}, sizeof(Haze::ScaleData)));
                    sendAll(RType::message::addComponent(newShot->getId(), "Hitbox", new Haze::HitboxData({0, 0, 32, 14}), sizeof(Haze::HitboxData)));
                    sendAll(RType::message::addComponent(newShot->getId(), "HitboxDisplay", nullptr, 0));
                    sendAll(RType::message::addComponent(newShot->getId(), "Velocity", new Haze::VelocityData{2, 0}, sizeof(Haze::VelocityData)));
                    sendAll(RType::message::addComponent(newShot->getId(), "Sprite", new Haze::SpriteData{"assets/sprites/shot.png"}, sizeof(Haze::SpriteData)));
                    sendAll(RType::message::addComponent(newShot->getId(), "Animation", new Haze::AnimationData{"assets/AnimationJSON/shot.json"}, sizeof(Haze::SpriteData)));
                    std::cout << "[SERVER] SEND SHOT\n";
                }

                auto velocity = dynamic_cast<Haze::Velocity *>(player.entity->getComponent("Velocity"));
                if (velocity == nullptr)
                    player.entity->addComponent(new Haze::Velocity(0, 0));
                velocity->x = 0;
                velocity->y = 0;

                if (IS_KEY_PRESSED(KEY_Z)) {
                    velocity->y += -10;
                }
                if (IS_KEY_PRESSED(KEY_Q)) {
                    velocity->x += -10;
                }
                if (IS_KEY_PRESSED(KEY_S)) {
                    velocity->y += 10;
                }
                if (IS_KEY_PRESSED(KEY_D)) {
                    velocity->x += 10;
                }
            },
            player.id));
}
