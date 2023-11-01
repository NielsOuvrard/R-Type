//
// Created by erwan on 10/15/23.
//

#include "Shot.h"

Shot::Shot(Haze::Engine &engine, network::data_channel<protocol::data> &channel, bool fromPlayer, uint16_t type, TypeEntities typeEntities)
    : _engine(engine), _channel(channel), _fromPlayer(fromPlayer), _type(type), _typeEntities(typeEntities)
{
}

void Shot::build(float x, float y)
{
    _entity = _engine.createEntity();
    std::cout << "["
              << _entity->getId()
              << "] Shot Created"
              << std::endl;
    _x = x;
    _y = y;
    _entity->addComponent(new Haze::Position(x, y));
    if (_fromPlayer) {
        _entity->addComponent(new Haze::Position(x + 20, y));
        _entity->addComponent(new Haze::Velocity(5, 0, 0.05));
        _entity->addComponent(new Haze::Scale(UNIVERSAL_SCALE, UNIVERSAL_SCALE));
    } else {
        _entity->addComponent(new Haze::Position(x - 20, y));
        _entity->addComponent(new Haze::Velocity(-5, 0, 0.05));
        _entity->addComponent(new Haze::Scale(UNIVERSAL_SCALE, -UNIVERSAL_SCALE));
    }
    _entity->addComponent(new Haze::Hitbox({{_typeEntities.shots[_type].hitBoxData.x,
                                             _typeEntities.shots[_type].hitBoxData.y,
                                             _typeEntities.shots[_type].hitBoxData.width,
                                             _typeEntities.shots[_type].hitBoxData.height}}));
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

void Shot::send()
{
    _channel.sendGroup(RType::message::createEntity(_entity->getId()));
    //_channel.sendGroup(RType::message::addComponent(_entity->getId(), "Damage", new Haze::DamageData{20}, sizeof(Haze::PositionData)));
    if (_fromPlayer) {
        _channel.sendGroup(RType::message::addComponent(_entity->getId(), "Position", new Haze::PositionData{_x + 20, _y}, sizeof(Haze::PositionData)));
        _channel.sendGroup(RType::message::addComponent(_entity->getId(), "Scale", new Haze::ScaleData{UNIVERSAL_SCALE, UNIVERSAL_SCALE}, sizeof(Haze::ScaleData)));
        _channel.sendGroup(RType::message::addComponent(_entity->getId(), "Velocity", new Haze::VelocityData{5, 0, 0.05}, sizeof(Haze::VelocityData)));
    } else {
        _channel.sendGroup(RType::message::addComponent(_entity->getId(), "Position", new Haze::PositionData{_x - 20, _y}, sizeof(Haze::PositionData)));
        _channel.sendGroup(RType::message::addComponent(_entity->getId(), "Scale", new Haze::ScaleData{-UNIVERSAL_SCALE, UNIVERSAL_SCALE}, sizeof(Haze::ScaleData)));
        _channel.sendGroup(RType::message::addComponent(_entity->getId(), "Velocity", new Haze::VelocityData{-5, 0, 0.05}, sizeof(Haze::VelocityData)));
    }

    auto elem_sprite = new Haze::SpriteData();
    strncpy(elem_sprite->path, _typeEntities.shots[_type].path_sprite.c_str(), sizeof(elem_sprite->path));
    elem_sprite->path[sizeof(elem_sprite->path) - 1] = '\0';
    _channel.sendGroup(RType::message::addComponent(_entity->getId(), "Sprite", elem_sprite, sizeof(Haze::SpriteData)));

    auto elem_animation = new Haze::AnimationData();
    strncpy(elem_animation->path, _typeEntities.shots[_type].path_json.c_str(), sizeof(elem_animation->path));
    elem_animation->path[sizeof(elem_animation->path) - 1] = '\0';
    _channel.sendGroup(RType::message::addComponent(_entity->getId(), "Animation", elem_animation, sizeof(Haze::AnimationData)));

    _channel.sendGroup(RType::message::addComponent(_entity->getId(), "Hitbox", new Haze::HitboxData({_typeEntities.shots[_type].hitBoxData.x, _typeEntities.shots[_type].hitBoxData.y, _typeEntities.shots[_type].hitBoxData.width, _typeEntities.shots[_type].hitBoxData.height}), sizeof(Haze::HitboxData)));
    _channel.sendGroup(RType::message::addComponent(_entity->getId(), "HitboxDisplay", nullptr, 0));
    _channel.sendGroup(RType::message::addComponent(_entity->getId(), "SpriteCropped", new Haze::SpriteCroppedData{2}, sizeof(Haze::SpriteCroppedData)));
}
