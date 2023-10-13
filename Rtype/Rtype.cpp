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
** Rtype
*/

#include "Rtype.hpp"
#include "data.h"
#include "net_data_channel.h"
#include "net_server.h"
#include "protocol.h"

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
            if (std::chrono::duration<double>(std::chrono::high_resolution_clock::now() - player.remote->lastActivity).count() > 5) {
                player.remote = nullptr;
            }
        }
    }
}

void Rtype::start()
{
    _running = true;
    while (_running) {
        // moveBackground(); // necessary for collision
        _engine.update();
        update(5, false);
        checkInactiveClients();
    }
}

void Rtype::stop()
{
    _running = false;
}

void Rtype::createPlayer(Player &client)
{
    Haze::Entity *newPlayer = _engine.createEntity();
    sendAll(RType::message::createEntity(newPlayer->getId()));
    std::cout << "Sent Entity\n";

    newPlayer->addComponent(new Haze::Velocity(0, 0));

    newPlayer->addComponent(new Haze::Position(100, 200));
    sendAll(RType::message::addComponent(newPlayer->getId(), "Position", new Haze::PositionData{100, 200}, sizeof(Haze::PositionData)));
    std::cout << "Sent Position\n";

    newPlayer->addComponent(new Haze::Scale(3, 3));
    sendAll(RType::message::addComponent(newPlayer->getId(), "Scale", new Haze::ScaleData{3, 3}, sizeof(Haze::ScaleData)));
    std::cout << "Sent Scale\n";

    newPlayer->addComponent(new Haze::Hitbox({{0, 0, 32, 14}}));
    sendAll(RType::message::addComponent(newPlayer->getId(), "Hitbox", new Haze::HitboxData({0, 0, 32, 14}), sizeof(Haze::HitboxData)));

    newPlayer->addComponent(new Haze::HitboxDisplay());
    sendAll(RType::message::addComponent(newPlayer->getId(), "HitboxDisplay", nullptr, 0));


    newPlayer->addComponent(new Haze::OnKeyPressed(
            [this, newPlayer](int i, std::vector<Haze::InputType> components) {
                if (std::find(components.begin(), components.end(), Haze::InputType::KEY_ENTER_INPUT) != components.end()) {
                    Haze::Entity *newShot = _engine.createEntity();
                    auto position = static_cast<Haze::Position *>(newPlayer->getComponent("Position"));
                    newShot->addComponent(new Haze::Position(position->x + 33 * 3, position->y));
                    newShot->addComponent(new Haze::Velocity(2, 0));
                    newShot->addComponent(new Haze::Scale(3, 3));
                    // TODO add hitbox, collider and send sprite, animation...
                    _entities.push_back(newShot);
                }

                auto velocity = static_cast<Haze::Velocity *>(newPlayer->getComponent("Velocity"));
                if (velocity == nullptr)
                    newPlayer->addComponent(new Haze::Velocity(0, 0));
                velocity->x = 0;
                velocity->y = 0;

                if (std::find(components.begin(), components.end(), Haze::InputType::KEY_UP_ARROW) != components.end()) {
                    velocity->y += -5;
                }
                if (std::find(components.begin(), components.end(), Haze::InputType::KEY_LEFT_ARROW) != components.end()) {
                    velocity->x += -5;
                }
                if (std::find(components.begin(), components.end(), Haze::InputType::KEY_DOWN_ARROW) != components.end()) {
                    velocity->y += 5;
                }
                if (std::find(components.begin(), components.end(), Haze::InputType::KEY_RIGHT_ARROW) != components.end()) {
                    velocity->x += 5;
                }
            }));
    newPlayer->addComponent(new Haze::Sprite("assets/r-typesheet30a.gif"));
    sendAll(RType::message::addComponent(newPlayer->getId(), "Sprite", new Haze::SpriteData{"assets/r-typesheet30a.gif"}, sizeof(Haze::SpriteData)));
    std::cout << "Sent Sprite\n";

    client.entity = newPlayer;
}

void Rtype::sendEverything(udp::endpoint &to)
{
    // * send to the new player all players data
    for (auto &player: _players) {

        auto now = std::chrono::system_clock::now();

        network::datagram<protocol::data> msg(protocol::data::create_entity);
        // TODO change with entity
        std::memcpy(msg.body.data(), static_cast<void *>(player.entity), sizeof(Haze::Component));
        sendTo(msg, to);


        Haze::Sprite *spaceshipSprite = new Haze::Sprite("assets/r-typesheet1.gif");
        network::datagram<protocol::data> msg_compo1(protocol::data::add_component);
        std::memcpy(msg_compo1.body.data(), static_cast<void *>(spaceshipSprite), sizeof(Haze::Component));
        sendTo(msg_compo1, to);
    }

    for (const std::string &type: _engine.getComponentList()->getComponentName()) {
        if (type == "Window") {
            break;
        }
        auto component = _engine.getComponentList()->getComponent(type, 0);

        // Haze::Component *info;
        network::datagram<protocol::data> msg_compo(protocol::data::add_component);

        std::memcpy(msg_compo.body.data(), static_cast<void *>(component), sizeof(Haze::Component));
        sendTo(msg_compo, to);
    }
}

void Rtype::onReceive(udp::endpoint from, network::datagram<protocol::data> content)
{
    switch (content.header.id) {
        case protocol::data::join: {
            // * if client is already connected
            for (auto &player: _players) {
                if (player.remote && player.remote->endpoint == from)
                    return;// refuse the connection
            }
            // * if didn't exist
            for (auto &player: _players) {
                if (!player.remote) {
                    player.remote = std::make_unique<Remote>(from);
                    //                    sendEverything(from);
                    createPlayer(player);
                    return;
                }
            }
            // ! Client was refused
            return;
        }

        case protocol::data::input: {
            Haze::info_inputs_weak info{};
            std::memcpy(&info, content.body.data(), content.header.size);
            Haze::info_inputs inputs;
            inputs.inputsPressed = std::vector<Haze::InputType>(info.pressedInputs.begin(), info.pressedInputs.end());
            inputs.inputsReleased = std::vector<Haze::InputType>(info.releasedInputs.begin(), info.releasedInputs.end());
            inputs.mouseType = info.mouseType;
            inputs.x = info.x;
            inputs.y = info.y;

            uint32_t id = findPlayerIndex(from);
            // between 1 and 4
            _engine.setInfoInputs(inputs, id);

            break;
        }
        case protocol::data::alive: {
            auto &player = findPlayer(from);
            player.remote->lastActivity = std::chrono::high_resolution_clock::now();
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
