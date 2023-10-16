//
// Created by erwan on 10/15/23.
//

#include "Missile.h"

Missile::Missile(Haze::Engine &engine, network::data_channel<protocol::data> &channel, Haze::Position *pos, bool isPlayer)
    : _engine(engine), _channel(channel), _pos(pos), _isPlayer(isPlayer)
{
}

void Missile::build()
{
    _entity = _engine.createEntity();
    Haze::Position *position = _pos;
    if (_pos == nullptr) {
        position = new Haze::Position(0, 0);
    }
    if (_isPlayer) {
        _entity->addComponent(new Haze::Position(position->x + 28, position->y));
        _entity->addComponent(new Haze::Velocity(2, 0));
        _entity->addComponent(new Haze::Scale(3, 3));
    } else {
        _entity->addComponent(new Haze::Position(position->x, position->y));
        _entity->addComponent(new Haze::Velocity(-2, 0));
        _entity->addComponent(new Haze::Scale(3, -3));
    }
    _entity->addComponent(new Haze::Hitbox({{0, 6, 16, 4}}));
    _entity->addComponent(new Haze::Damage(20));


    // TODO: Add lifetime to missile


    std::map<std::string, Haze::Collision::CollisionInfo> mapCollision;
    mapCollision["enemy"] = {
            Haze::Collision::LAMBDA,
            0.1,
            [this](int a, int b) {
                if (!_entity) {
                    return;
                }
                _channel.sendAll(RType::message::deleteEntity(_entity->getId()));
                _entity->addComponent(new Haze::Destroy());
                std::cout << "Missile hit enemy" << std::endl;
                _entity = nullptr;
            }};
    _entity->addComponent(new Haze::Collision("missile", mapCollision));

    send();
}

void Missile::send()
{
    auto position = dynamic_cast<Haze::Position *>(_entity->getComponent("Position"));
    _channel.sendAll(RType::message::createEntity(_entity->getId()));
    //_channel.sendAll(RType::message::addComponent(_entity->getId(), "Damage", new Haze::DamageData{20}, sizeof(Haze::PositionData)));
    if (_isPlayer) {
        _channel.sendAll(RType::message::addComponent(_entity->getId(), "Position", new Haze::PositionData{position->x + 28, position->y}, sizeof(Haze::PositionData)));
        _channel.sendAll(RType::message::addComponent(_entity->getId(), "Scale", new Haze::ScaleData{3, 3}, sizeof(Haze::ScaleData)));
        _channel.sendAll(RType::message::addComponent(_entity->getId(), "Velocity", new Haze::VelocityData{2, 0}, sizeof(Haze::VelocityData)));
    } else {
        _channel.sendAll(RType::message::addComponent(_entity->getId(), "Position", new Haze::PositionData{position->x, position->y}, sizeof(Haze::PositionData)));
        _channel.sendAll(RType::message::addComponent(_entity->getId(), "Scale", new Haze::ScaleData{-3, 3}, sizeof(Haze::ScaleData)));
        _channel.sendAll(RType::message::addComponent(_entity->getId(), "Velocity", new Haze::VelocityData{-2, 0}, sizeof(Haze::VelocityData)));
    }
    _channel.sendAll(RType::message::addComponent(_entity->getId(), "Hitbox", new Haze::HitboxData({0, 6, 16, 4}), sizeof(Haze::HitboxData)));
    _channel.sendAll(RType::message::addComponent(_entity->getId(), "HitboxDisplay", nullptr, 0));
    _channel.sendAll(RType::message::addComponent(_entity->getId(), "Sprite", new Haze::SpriteData{"assets/sprites/shot.png"}, sizeof(Haze::SpriteData)));
    _channel.sendAll(RType::message::addComponent(_entity->getId(), "Animation", new Haze::AnimationData{"assets/AnimationJSON/shot.json"}, sizeof(Haze::AnimationData)));
    _channel.sendAll(RType::message::addComponent(_entity->getId(), "SpriteCropped", new Haze::SpriteCroppedData{2}, sizeof(Haze::SpriteCroppedData)));
}
