//
// Created by erwan on 10/15/23.
//

#include "Enemy.h"

#define IS_KEY_PRESSED(key) (std::find(components.begin(), components.end(), Haze::InputType::key) != components.end())

Enemy::Enemy(Haze::Engine &engine, network::data_channel<protocol::data> &channel)
    : _engine(engine), _channel(channel)
{
}

void Enemy::shoot()
{
    if (_missileCd.IsReady()) {
        std::cout << "Enemy shoot" << std::endl;
        auto position = dynamic_cast<Haze::Position *>(this->_entity->getComponent("Position"));
        _missiles.emplace_back(_engine, _channel, position, false);
        _missiles.back().build();
        _missileCd.Activate();
    }
}

void Enemy::build()
{
    _missileCd.Activate();
    _entity = _engine.createEntity();
    _entity->addComponent(new Haze::Position(500, 300));
    //    _entity->addComponent(new Haze::Velocity(-2, 0));
    _entity->addComponent(new Haze::Scale(3, 3));
    _entity->addComponent(new Haze::Hitbox({{5, 5, 33 - 10, 36 - 10}}));


    std::map<std::string, Haze::Collision::CollisionInfo> mapCollision;
    mapCollision["missile"] = {
            Haze::Collision::LAMBDA,
            0.1,
            [this](int a, int b) {
                if (!_entity) {
                    return;
                }
                auto damage = dynamic_cast<Haze::Damage *>(_engine.getEntity(b)->getComponent("Damage"));
                if (damage == nullptr) {
                    std::cout << "Error: Damage component not found" << std::endl;
                    return;
                }
                std::cout << "hp = " << _hp << " - " << damage->damage << " = " << _hp - damage->damage << std::endl;
                if (_hp - damage->damage < 0) {
                    _channel.sendAll(RType::message::deleteEntity(_entity->getId()));
                    _entity->addComponent(new Haze::Destroy());
                    _entity = nullptr;
                } else {
                    _hp -= damage->damage;
                }
                std::cout << "Enemy not die 2, the come back\n";
            }};

    mapCollision["player"] = {
            Haze::Collision::LAMBDA,
            0.1,
            [this](int a, int b) {
                if (!_entity) {
                    return;
                }
                std::cout << "enemy die by tutching player\n";
                _channel.sendAll(RType::message::deleteEntity(_entity->getId()));
                _entity->addComponent(new Haze::Destroy());
                _entity = nullptr;
                std::cout << "Enemy not die 2, the come back\n";
            }};
    _entity->addComponent(new Haze::Collision("enemy", mapCollision));
    send();
}

void Enemy::send()
{
    _channel.sendGroup(RType::message::createEntity(_entity->getId()));

    _channel.sendGroup(RType::message::addComponent(_entity->getId(), "Health", new Haze::HealthData{50}, sizeof(Haze::HealthData)));
    _channel.sendGroup(RType::message::addComponent(_entity->getId(), "Position", new Haze::PositionData{500, 300}, sizeof(Haze::PositionData)));
    //    _channel.sendGroup(RType::message::addComponent(_entity->getId(), "Velocity", new Haze::VelocityData{-2, 0}, sizeof(Haze::VelocityData)));
    _channel.sendGroup(RType::message::addComponent(_entity->getId(), "Scale", new Haze::ScaleData{3, 3}, sizeof(Haze::ScaleData)));
    _channel.sendGroup(RType::message::addComponent(_entity->getId(), "Hitbox", new Haze::HitboxData{5, 5, 33 - 10, 36 - 10}, sizeof(Haze::HitboxData)));
    _channel.sendGroup(RType::message::addComponent(_entity->getId(), "HitboxDisplay", nullptr, 0));
    _channel.sendGroup(RType::message::addComponent(_entity->getId(), "Sprite", new Haze::SpriteData{"assets/sprites/enemy.gif"}, sizeof(Haze::SpriteData)));
    _channel.sendGroup(RType::message::addComponent(_entity->getId(), "Animation", new Haze::AnimationData{"assets/AnimationJSON/enemy.json"}, sizeof(Haze::AnimationData)));
}
