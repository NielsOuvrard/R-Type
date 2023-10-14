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
        if (player.remote) {
            auto highResNow = std::chrono::high_resolution_clock::now();

            std::chrono::duration<double> duration = highResNow.time_since_epoch() - player.remote->lastActivity.time_since_epoch();

            if (duration.count() > 5.0) {
                player.remote = nullptr;
            }
        }
    }
}

void Rtype::start()
{_running = true;
    std::chrono::steady_clock::time_point previousTime = std::chrono::steady_clock::now();
    const std::chrono::milliseconds targetFrameTime(1000 / 60); // 60 FPS

    while (_running) {
        // moveBackground(); // necessary for collision
        _engine.update();
        update(5, false);
        checkInactiveClients();

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

void Rtype::createPlayer(Player &client)
{
    Haze::Entity *newPlayer = _engine.createEntity();
    newPlayer->addComponent(new Haze::Velocity(0, 0));
    newPlayer->addComponent(new Haze::Position(100, 200));
    newPlayer->addComponent(new Haze::Scale(3, 3));
    newPlayer->addComponent(new Haze::Hitbox({{0, 0, 32, 14}}));

    sendAll(RType::message::createEntity(newPlayer->getId()));
    sendAll(RType::message::addComponent(newPlayer->getId(), "Position", new Haze::PositionData{100, 200}, sizeof(Haze::PositionData)));
    sendAll(RType::message::addComponent(newPlayer->getId(), "Scale", new Haze::ScaleData{3, 3}, sizeof(Haze::ScaleData)));
    sendAll(RType::message::addComponent(newPlayer->getId(), "Hitbox", new Haze::HitboxData({0, 0, 32, 14}), sizeof(Haze::HitboxData)));
    sendAll(RType::message::addComponent(newPlayer->getId(), "HitboxDisplay", nullptr, 0));
    sendAll(RType::message::addComponent(newPlayer->getId(), "Sprite", new Haze::SpriteData{"assets/r-typesheet30a.gif"}, sizeof(Haze::SpriteData)));

    // ! animation didn't work, receive {0, 0, 0, 0}
    //    sendAll(RType::message::addComponent(newPlayer->getId(), "Animation", new Haze::AnimationData({
    //        {
    //        {0, 0, 34, 34},
    //        {34, 0, 34, 34},
    //        {68, 0, 34, 34}
    //        },
    //        Haze::Animation::AnimationType::LOOP,
    //        true, 0.2
    //        }), sizeof(Haze::AnimationData)));

    newPlayer->addComponent(new Haze::OnKeyPressed(
            [this, newPlayer](int i, std::vector<Haze::InputType> components) {
                auto currentTimeShot = std::chrono::steady_clock::now();
                auto lastShotTime = _players[newPlayer->getId()].lastShot;
                auto durationShot = std::chrono::duration_cast<std::chrono::milliseconds>(currentTimeShot - lastShotTime);
                if (IS_KEY_PRESSED(KEY_F) && (durationShot >= std::chrono::seconds(1))) {
                    // * reset the clock
                    _players[newPlayer->getId()].lastShot = std::chrono::steady_clock::now();
                    // * create shot
                    Haze::Entity *newShot = _engine.createEntity();
                    auto position = dynamic_cast<Haze::Position *>(newPlayer->getComponent("Position"));
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
                    sendAll(RType::message::addComponent(newShot->getId(), "Sprite", new Haze::SpriteData{"assets/shot.png"}, sizeof(Haze::SpriteData)));
                    std::cout << "[SERVER] SEND SHOT\n";
                }

                auto currentTime = std::chrono::steady_clock::now();
                auto lastMoveTime = _players[newPlayer->getId()].lastMove;
                auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - lastMoveTime);
                if ((IS_KEY_PRESSED(KEY_Z) || IS_KEY_PRESSED(KEY_Q) || IS_KEY_PRESSED(KEY_S) || IS_KEY_PRESSED(KEY_D)) && (duration >= std::chrono::microseconds(500))) {
                    // ! This code is for the next usage of Vector
                    // ! maybe not delet it
                    //                auto velocity = dynamic_cast<Haze::Velocity *>(newPlayer->getComponent("Velocity"));
                    //                if (velocity == nullptr)
                    //                    newPlayer->addComponent(new Haze::Velocity(0, 0));
                    //                velocity->x = 0;
                    _players[newPlayer->getId()].lastMove = std::chrono::steady_clock::now();
                    //                velocity->y = 0;
                    auto position = dynamic_cast<Haze::Position *>(newPlayer->getComponent("Position"));

                    if (IS_KEY_PRESSED(KEY_Z)) {
                        sendAll(RType::message::addComponent(newPlayer->getId(), "Position", new Haze::PositionData{position->x, position->y + 5}, sizeof(Haze::PositionData)));
                        position->y -= 5;
                        //                    velocity->y += -5;
                    }
                    if (IS_KEY_PRESSED(KEY_Q)) {
                        sendAll(RType::message::addComponent(newPlayer->getId(), "Position", new Haze::PositionData{position->x - 5, position->y}, sizeof(Haze::PositionData)));
                        position->x += -5;
                        //                    velocity->x += -5;
                    }
                    if (IS_KEY_PRESSED(KEY_S)) {
                        sendAll(RType::message::addComponent(newPlayer->getId(), "Position", new Haze::PositionData{position->x, position->y - 5}, sizeof(Haze::PositionData)));
                        position->y += 5;
                        //                    velocity->y += 5;
                    }
                    if (IS_KEY_PRESSED(KEY_D)) {
                        sendAll(RType::message::addComponent(newPlayer->getId(), "Position", new Haze::PositionData{position->x + 5, position->y}, sizeof(Haze::PositionData)));
                        position->x += 5;
                        //                    velocity->x += 5;
                    }
                    newPlayer->addComponent(new Haze::Position(position->x, position->y));
                    //                if (velocity->x != 0 || velocity->y != 0) {
                    //                    std::cout << "velocity: " << velocity->x << ", " << velocity->y << std::endl;
                    //                    sendAll(RType::message::addComponent(newPlayer->getId(), "Velocity", new Haze::VelocityData{velocity->x, velocity->y}, sizeof(Haze::VelocityData)));
                    //                }
                }
            }));
    // ! This code is for the next usage of Vector
    // ! maybe not delet it
    // newPlayer->addComponent(new Haze::OnKeyReleased(
    //         [this, newPlayer](int i, std::vector<Haze::InputType> components) {
    //             //                    auto velocity = dynamic_cast<Haze::Velocity *>(newPlayer->getComponent("Velocity"));
    //             //                    if (velocity != nullptr && (velocity->x != 0 || velocity->y != 0)) {
    //             //                        if ((IS_KEY_PRESSED(KEY_Z)) || (IS_KEY_PRESSED(KEY_Q)) || (IS_KEY_PRESSED(KEY_S)) || (IS_KEY_PRESSED(KEY_D))) {
    //             //                            std::cout << "velocity reset\n";
    //             //                            sendAll(RType::message::addComponent(newPlayer->getId(), "Velocity", new Haze::VelocityData{velocity->x, velocity->y}, sizeof(Haze::VelocityData)));
    //             //                        }
    //             //                    }
    //             auto position = dynamic_cast<Haze::Position *>(newPlayer->getComponent("Position"));

    //             if (IS_KEY_PRESSED(KEY_Z) || IS_KEY_PRESSED(KEY_Q) || IS_KEY_PRESSED(KEY_S) || IS_KEY_PRESSED(KEY_D)) {
    //                 // sendAll(RType::message::addComponent(newPlayer->getId(), "Position", new Haze::PositionData{position->x, position->y + 5}, sizeof(Haze::PositionData)));
    //                 // position->y += 5;
    //             }
    //             newPlayer->addComponent(new Haze::Position(position->x, position->y));
    //         }));

    client.entity = newPlayer;
}

void Rtype::sendEverything(udp::endpoint &to)
{
    // * send to the new player all players data
    for (auto &player: _players) {
        if (player.remote && player.entity) {
            std::cout << "PLAYER SEND\n";
            std::cout << "PLAYER ID = " << player.entity->getId() << "\n";
            sendTo(RType::message::createEntity(player.entity->getId()), to);
            sendTo(RType::message::addComponent(player.entity->getId(), "Position", player.entity->getComponent("Position"), sizeof(Haze::PositionData)), to);
            sendTo(RType::message::addComponent(player.entity->getId(), "Scale", player.entity->getComponent("Scale"), sizeof(Haze::ScaleData)), to);
            std::cout << "SEND SCALE\n";
            sendTo(RType::message::addComponent(player.entity->getId(), "Hitbox", player.entity->getComponent("Hitbox"), sizeof(Haze::HitboxData)), to);
            std::cout << "SEND HITBOX\n";
            sendAll(RType::message::addComponent(player.entity->getId(), "Sprite", new Haze::SpriteData{"assets/r-typesheet30a.gif"}, sizeof(Haze::SpriteData)));
            std::cout << "SEND SPRITE\n";
            sendTo(RType::message::addComponent(player.entity->getId(), "HitboxDisplay", nullptr, 0), to);
            std::cout << "PLAYER ID SENT\n";
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

void Rtype::onReceive(udp::endpoint from, network::datagram<protocol::data> content)
{
    switch (content.header.id) {
        case protocol::data::join: {
            std::cout << "[SERVER] RECEIVE JOIN\n";
            // * if client is already connected
            for (auto &player: _players) {
                if (player.remote && player.remote->endpoint == from)
                    return;// refuse the connection
            }
            // * if didn't exist
            for (auto &player: _players) {
                if (!player.remote) {
                    std::cout << "[SERVER] found place\n";
                    player.remote = std::make_unique<Remote>(from);
                    std::cout << "[SERVER] CREATE REMOTE\n";
                    sendEverything(from);
                    std::cout << "[SERVER] SENT EVERYTHING\n";
                    createPlayer(player);
                    std::cout << "[SERVER] CREATE PLAYER\n";
                    return;
                }
            }
            // ! Client was refused
            return;
        }

        case protocol::data::input: {
            //             ? sorry Clovis, this didn't work
            Haze::info_inputs_weak info{};
            std::memcpy(&info, content.body.data(), content.header.size);
            Haze::info_inputs inputs;
            for (auto &key: info.pressedInputs) {
                if (key != Haze::NO) {
                    inputs.inputsPressed.push_back(key);
                    std::cout << "pressed " << 'a' + key << std::endl;
                }
            }
            for (auto &key: info.releasedInputs) {
                if (key != Haze::NO) {
                    inputs.inputsReleased.push_back(key);
                    std::cout << "released " << key << std::endl;
                }
            }
            inputs.mouseType = info.mouseType;
            inputs.x = info.x;
            inputs.y = info.y;
            if (inputs.inputsReleased.size() > 1) {
                std::cout << "not empty\n";
            }

            //            Haze::InputType keyFound;
            //            std::memcpy(&keyFound, content.body.data(), 1);
            //            Haze::InputType keyReleased;
            //            std::memcpy(&keyReleased, content.body.data() + 1, 1);
            //            Haze::info_inputs inputs{};
            //            inputs.inputsPressed.push_back(keyFound);
            //            inputs.inputsReleased.push_back(keyFound);

            uint32_t id = findPlayerIndex(from) - 1;
            _engine.setInfoInputs(inputs, id);
            break;
        }
        case protocol::data::alive: {
            auto &player = findPlayer(from);
            std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
            player.remote->lastActivity = now;
            break;
        }
        default: {
            break;
        }
    }
}

// TODO: change the return type to a shared_ptr
Rtype::Player &Rtype::findPlayer(const udp::endpoint &endpoint)
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
