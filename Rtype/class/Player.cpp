//
// Created by erwan on 10/15/23.
//

#include "Player.h"

#define IS_KEY_PRESSED(key) (std::find(components.begin(), components.end(), Haze::InputType::key) != components.end())

Player::Player(Haze::Engine &engine, network::data_channel<protocol::data> &channel, uint32_t id)
    : _engine(engine), _channel(channel), _id(id)
{
}

void Player::build()
{
    std::cout << "\x1B[31m"
              << "CREATE PLAYER"
              << _id
              << "\n\x1B[0m";
    _entity = _engine.createEntity();
    _entity->addComponent(new Haze::Velocity(0, 0));
    _entity->addComponent(new Haze::Position(100, 200));
    _entity->addComponent(new Haze::Scale(3, 3));
    _entity->addComponent(new Haze::Hitbox({{0, 0, 32, 14}}));
    _entity->addComponent(new Haze::OnKeyPressed(
            [this](int actor, std::vector<Haze::InputType> components) {
                if (IS_KEY_PRESSED(KEY_F)) { // && _missileCd.IsReady() // ! didn't work, why ?
                    _missileCd.Activate();
                    auto position = dynamic_cast<Haze::Position *>(this->_entity->getComponent("Position"));
                    _missiles.emplace_back(_engine, _channel, position);
                    _missiles.back().build();
                }

                auto velocity = dynamic_cast<Haze::Velocity *>(_entity->getComponent("Velocity"));
                if (velocity == nullptr) {
                    _entity->addComponent(new Haze::Velocity(0, 0));
                    velocity = dynamic_cast<Haze::Velocity *>(_entity->getComponent("Velocity"));
                }
                velocity->x = 0;
                velocity->y = 0;

                if (IS_KEY_PRESSED(KEY_Z)) {
                    velocity->y += -10;
                    sendUpdate();
                }
                if (IS_KEY_PRESSED(KEY_Q)) {
                    velocity->x += -10;
                    sendUpdate();
                }
                if (IS_KEY_PRESSED(KEY_S)) {
                    velocity->y += 10;
                    sendUpdate();
                }
                if (IS_KEY_PRESSED(KEY_D)) {
                    velocity->x += 10;
                    sendUpdate();
                }
            },
            _id));

    send();
}

void Player::send()
{
    // TODO: Free allocated Data created with new
    auto pos = dynamic_cast<Haze::Position *>(_entity->getComponent("Position"));
    auto scale = dynamic_cast<Haze::Scale *>(_entity->getComponent("Scale"));
    auto hitbox = dynamic_cast<Haze::Hitbox *>(_entity->getComponent("Hitbox"))->hitbox.front();

    _channel.sendAll(RType::message::createEntity(_entity->getId()));
    _channel.sendAll(RType::message::addComponent(_entity->getId(), "Position", new Haze::PositionData{pos->x, pos->y}, sizeof(Haze::PositionData)));
    _channel.sendAll(RType::message::addComponent(_entity->getId(), "Scale", new Haze::ScaleData{scale->x, scale->y}, sizeof(Haze::ScaleData)));
    _channel.sendAll(RType::message::addComponent(_entity->getId(), "Hitbox", new Haze::HitboxData{hitbox}, sizeof(Haze::HitboxData)));

    _channel.sendAll(RType::message::addComponent(_entity->getId(), "HitboxDisplay", nullptr, 0));
    _channel.sendAll(RType::message::addComponent(_entity->getId(), "Sprite", new Haze::SpriteData{"assets/sprites/spaceship.gif"}, sizeof(Haze::SpriteData)));
    _channel.sendAll(RType::message::addComponent(_entity->getId(), "Animation", new Haze::AnimationData{"assets/AnimationJSON/spaceship.json"}, sizeof(Haze::AnimationData)));
}

void Player::sendUpdate()
{
    auto pos = dynamic_cast<Haze::Position *>(_entity->getComponent("Position"));
    //    auto scale = dynamic_cast<Haze::Scale *>(_entity->getComponent("Scale"));
    //    auto hitbox = dynamic_cast<Haze::Hitbox *>(_entity->getComponent("Hitbox"))->hitbox.front();

    _channel.sendAll(RType::message::addComponent(_entity->getId(), "Position", new Haze::PositionData{pos->x, pos->y}, sizeof(Haze::PositionData)));
    //    _channel.sendAll(RType::message::addComponent(_entity->getId(), "Scale", new Haze::ScaleData{scale->x, scale->y}, sizeof(Haze::ScaleData)));
    //    _channel.sendAll(RType::message::addComponent(_entity->getId(), "Hitbox", new Haze::HitboxData{hitbox}, sizeof(Haze::HitboxData)));
}
