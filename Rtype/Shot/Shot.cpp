//
// Created by erwan on 10/15/23.
//

#include "Shot.h"

Shot::Shot(DataGame dataGame, TypeEntities typeEntities, uint16_t type, float vector_x, float vector_y, std::string sender)
    : _dataGame(dataGame), _typeEntities(typeEntities), _type(type), _x(0), _y(0), _vector_x(vector_x), _vector_y(vector_y), _sender(sender)
{
}

void Shot::build(float x, float y)
{
    _entity = _dataGame.engine.createEntity();
    std::cout << "[" << _entity->getId() << "] Shot Created" << std::endl;
    _x = x;
    _y = y;
    _entity->addComponent(new Haze::Position(x, y));
    _entity->addComponent(new Haze::Position(x, y));

    if (!_typeEntities.shots[_type].sound.empty()) {
        // create sound at the launch
        auto elem_sound = new Haze::AnimationData();
        strncpy(elem_sound->path, _typeEntities.shots[_type].sound.c_str(), sizeof(elem_sound->path));
        elem_sound->path[sizeof(elem_sound->path) - 1] = '\0';
        _dataGame.channel.sendGroup(RType::message::addComponent(_entity->getId(), "Audio", elem_sound, sizeof(Haze::AudioData)));
    }

    if (_typeEntities.shots[_type].bullet_drop) {
        float drop_degree = _typeEntities.shots[_type].bullet_drop_degree * (_vector_x >= 0 ? 1.0 : -1.0);
        _entity->addComponent(new Haze::BulletDrop((_vector_x * _typeEntities.shots[_type].velocity), drop_degree, 0.05));
    } else {
        _entity->addComponent(new Haze::Velocity(
                (_vector_x * _typeEntities.shots[_type].velocity),
                (_vector_y * _typeEntities.shots[_type].velocity),
                0.05));
    }
    _entity->addComponent(new Haze::Scale(UNIVERSAL_SCALE * (_vector_x >= 0 ? 1 : -1), UNIVERSAL_SCALE));
    _entity->addComponent(new Haze::Hitbox({{_typeEntities.shots[_type].hitBoxData.x,
                                             _typeEntities.shots[_type].hitBoxData.y,
                                             _typeEntities.shots[_type].hitBoxData.width,
                                             _typeEntities.shots[_type].hitBoxData.height}}));
    _entity->addComponent(new Haze::Damage(20));


    if (_sender == "player") {
        std::map<std::string, Haze::Collision::CollisionInfo> collision_enemy;

        collision_enemy["enemy"] = {
                Haze::Collision::LAMBDA,
                0.1,
                [this](int a, int b) {
                    if (!_entity) {
                        return;
                    }
                    _dataGame.channel.sendGroup(RType::message::deleteEntity(_entity->getId()));
                    _entity->addComponent(new Haze::Destroy());
                    _entity = nullptr;
                }};
        _entity->addComponent(new Haze::Collision("missile", collision_enemy));

    } else if (_sender == "enemy") {
        std::map<std::string, Haze::Collision::CollisionInfo> collision_player;

        collision_player["player"] = {
                Haze::Collision::LAMBDA,
                0.1,
                [this](int a, int b) {
                    if (!_entity) {
                        return;
                    }
                    _dataGame.channel.sendGroup(RType::message::deleteEntity(_entity->getId()));
                    _entity->addComponent(new Haze::Destroy());
                    _entity = nullptr;
                }};
        _entity->addComponent(new Haze::Collision("missile-enemy", collision_player));
    }

    send();
}

void Shot::send()
{
    _dataGame.channel.sendGroup(RType::message::createEntity(_entity->getId()));
    _dataGame.channel.sendGroup(RType::message::addComponent(_entity->getId(), "Position", new Haze::PositionData{_x, _y}, sizeof(Haze::PositionData)));

    if (_typeEntities.shots[_type].bullet_drop) {
        float drop_degree = _typeEntities.shots[_type].bullet_drop_degree * (_vector_x >= 0 ? 1.0 : -1.0);
        _dataGame.channel.sendGroup(RType::message::addComponent(_entity->getId(), "BulletDrop", new Haze::BulletDropData{(_vector_x * _typeEntities.shots[_type].velocity), drop_degree, 0.1}, sizeof(Haze::BulletDropData)));
    } else {
        _dataGame.channel.sendGroup(RType::message::addComponent(_entity->getId(), "Velocity", new Haze::VelocityData{(_vector_x * _typeEntities.shots[_type].velocity), (_vector_y * _typeEntities.shots[_type].velocity), 0.05}, sizeof(Haze::VelocityData)));
    }

    _dataGame.channel.sendGroup(RType::message::addComponent(_entity->getId(), "Hitbox", new Haze::HitboxData({_typeEntities.shots[_type].hitBoxData.x, _typeEntities.shots[_type].hitBoxData.y, _typeEntities.shots[_type].hitBoxData.width, _typeEntities.shots[_type].hitBoxData.height}), sizeof(Haze::HitboxData)));
    //_dataGame.channel.sendGroup(RType::message::addComponent(_entity->getId(), "HitboxDisplay", nullptr, 0));
    if (_typeEntities.shots[_type].no_animation) {
        _dataGame.channel.sendGroup(RType::message::addComponent(_entity->getId(), "SpriteCropped", new Haze::SpriteCroppedData{0}, sizeof(Haze::SpriteCroppedData)));
    }

    auto elem_scale = new Haze::ScaleData();
    elem_scale->x = UNIVERSAL_SCALE * (_vector_x >= 0 ? 1.0 : -1.0);
    elem_scale->y = UNIVERSAL_SCALE;
    _dataGame.channel.sendGroup(RType::message::addComponent(_entity->getId(), "Scale", elem_scale, sizeof(Haze::ScaleData)));

    auto elem_sprite = new Haze::SpriteData();
    strncpy(elem_sprite->path, _typeEntities.shots[_type].path_sprite.c_str(), sizeof(elem_sprite->path));
    elem_sprite->path[sizeof(elem_sprite->path) - 1] = '\0';
    _dataGame.channel.sendGroup(RType::message::addComponent(_entity->getId(), "Sprite", elem_sprite, sizeof(Haze::SpriteData)));

    auto elem_animation = new Haze::AnimationData();
    strncpy(elem_animation->path, _typeEntities.shots[_type].path_json.c_str(), sizeof(elem_animation->path));
    elem_animation->path[sizeof(elem_animation->path) - 1] = '\0';
    _dataGame.channel.sendGroup(RType::message::addComponent(_entity->getId(), "Animation", elem_animation, sizeof(Haze::AnimationData)));
}

void Shot::stopVelocity()// useless
{
}