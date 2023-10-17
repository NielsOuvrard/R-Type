//
// Created by erwan on 10/15/23.
//

#include "Missile.h"

Missile::Missile(Haze::Engine &engine, network::data_channel<protocol::data> &channel, bool fromPlayer)
    : _engine(engine), _channel(channel), _fromPlayer(fromPlayer)
{
}

void Missile::build(float x, float y)
{
    _entity = _engine.createEntity();
    std::cout << "["
              << _entity->getId()
              << "] Missile Created"
              << std::endl;

    _entity->addComponent(new Haze::Position(x, y));
    if (_fromPlayer) {
        _entity->addComponent(new Haze::Position(x + 20, y));
        _entity->addComponent(new Haze::Velocity(2, 0));
        _entity->addComponent(new Haze::Scale(3, 3));
    } else {
        _entity->addComponent(new Haze::Position(x - 20, y));
        _entity->addComponent(new Haze::Velocity(-2, 0));
        _entity->addComponent(new Haze::Scale(3, -3));
    }
    _entity->addComponent(new Haze::Hitbox({{0, 6, 16, 4}}));
    _entity->addComponent(new Haze::Damage(20));


    // TODO: Add lifetime to missile

    if (_fromPlayer) {
        std::map<std::string, Haze::Collision::CollisionInfo> mapCollision;
        mapCollision["enemy"] = {
                Haze::Collision::LAMBDA,
                0.1,
                [this](int a, int b) {
                    if (!_entity) {
                        return;
                    }
                    _channel.sendGroup(RType::message::deleteEntity(_entity->getId()));
                    _entity->addComponent(new Haze::Destroy());
                    _entity = nullptr;
                }};
        _entity->addComponent(new Haze::Collision("missile", mapCollision));
    } else {
        std::map<std::string, Haze::Collision::CollisionInfo> mapCollision;
        mapCollision["player"] = {
                Haze::Collision::LAMBDA,
                0.1,
                [this](int a, int b) {
                    if (!_entity) {
                        return;
                    }
                    _channel.sendGroup(RType::message::deleteEntity(_entity->getId()));
                    _entity->addComponent(new Haze::Destroy());
                    _entity = nullptr;
                }};
        _entity->addComponent(new Haze::Collision("missile-enemy", mapCollision));
    }
    send();
}

void Missile::send()
{
    Haze::Position *position = _pos;
    if (_pos == nullptr) {
        position = new Haze::Position(0, 0);
    }
    _channel.sendGroup(RType::message::createEntity(_entity->getId()));
    //_channel.sendGroup(RType::message::addComponent(_entity->getId(), "Damage", new Haze::DamageData{20}, sizeof(Haze::PositionData)));
    if (_fromPlayer) {
        _channel.sendGroup(RType::message::addComponent(_entity->getId(), "Position", new Haze::PositionData{position->x + 28, position->y}, sizeof(Haze::PositionData)));
        _channel.sendGroup(RType::message::addComponent(_entity->getId(), "Scale", new Haze::ScaleData{3, 3}, sizeof(Haze::ScaleData)));
        _channel.sendGroup(RType::message::addComponent(_entity->getId(), "Velocity", new Haze::VelocityData{2, 0}, sizeof(Haze::VelocityData)));
        _channel.sendGroup(RType::message::addComponent(_entity->getId(), "Sprite", new Haze::SpriteData{"assets/sprites/shot.png"}, sizeof(Haze::SpriteData)));
    } else {
        _channel.sendGroup(RType::message::addComponent(_entity->getId(), "Position", new Haze::PositionData{position->x, position->y + 15}, sizeof(Haze::PositionData)));
        _channel.sendGroup(RType::message::addComponent(_entity->getId(), "Scale", new Haze::ScaleData{-3, 3}, sizeof(Haze::ScaleData)));
        _channel.sendGroup(RType::message::addComponent(_entity->getId(), "Velocity", new Haze::VelocityData{-2, 0}, sizeof(Haze::VelocityData)));
        _channel.sendGroup(RType::message::addComponent(_entity->getId(), "Sprite", new Haze::SpriteData{"assets/sprites/shot-enemy.png"}, sizeof(Haze::SpriteData)));
    }
    _channel.sendGroup(RType::message::addComponent(_entity->getId(), "Hitbox", new Haze::HitboxData({0, 6, 16, 4}), sizeof(Haze::HitboxData)));
    _channel.sendGroup(RType::message::addComponent(_entity->getId(), "HitboxDisplay", nullptr, 0));
    _channel.sendGroup(RType::message::addComponent(_entity->getId(), "Animation", new Haze::AnimationData{"assets/AnimationJSON/shot.json"}, sizeof(Haze::AnimationData)));
    _channel.sendGroup(RType::message::addComponent(_entity->getId(), "SpriteCropped", new Haze::SpriteCroppedData{2}, sizeof(Haze::SpriteCroppedData)));
}
