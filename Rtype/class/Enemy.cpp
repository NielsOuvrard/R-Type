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
        _missileCd.Activate();
        auto position = dynamic_cast<Haze::Position *>(_entity->getComponent("Position"));
        _missiles.emplace_back(std::make_unique<Missile>(_engine, _channel, false));
        _missiles.back()->build(position->x, position->y);
    }
}

void Enemy::build()
{
    int x = std::rand() % 100 + 10;
    int y = std::rand() % 550 + 50;
    std::chrono::milliseconds d((std::rand() % 10 + 5) * 1000);
    _missileCd.setDuration(d);

    _missileCd.Activate();
    _entity = _engine.createEntity();
    std::cout << "[" << _entity->getId() << "] Enemy Created" << std::endl;
    _entity->addComponent(new Haze::Position(800 + x, y));
    _entity->addComponent(new Haze::Velocity(-1.5, 0));
    _entity->addComponent(new Haze::Scale(3, 3));
    _entity->addComponent(new Haze::Hitbox({{5, 5, 33 - 10, 36 - 10}}));

    std::map<std::string, Haze::Collision::CollisionInfo> mapCollision;
    mapCollision["missile"] = {
            Haze::Collision::LAMBDA,
            0.1,
            [this](int a, int b) {
                //                if (!_entity) {
                //                    return;
                //                }
                auto damage = dynamic_cast<Haze::Damage *>(_engine.getEntity(b)->getComponent("Damage"));
                if (damage == nullptr) {
                    return;
                }
                _hp -= damage->damage;
                if (_hp <= 0) {
                    auto position = dynamic_cast<Haze::Position *>(_entity->getComponent("Position"));
                    _pos_x = position->x;
                    _pos_y = position->y;
                    std::cout << "enemy die by missile player\n";
                    _channel.sendGroup(RType::message::deleteEntity(_entity->getId()));
                    _entity->addComponent(new Haze::Destroy());
                    _entity = nullptr;
                    this->_isDead = true;
                } else {
                    std::cout << "enemy damage by missile player: " << damage->damage << " hp: " << _hp << "\n";
                    _hp -= damage->damage;
                }
            }};

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
    _entity->addComponent(new Haze::Collision("enemy", mapCollision));
    send();
}

void Enemy::send()
{
    auto pos = dynamic_cast<Haze::Position *>(_entity->getComponent("Position"));
    _channel.sendGroup(RType::message::createEntity(_entity->getId()));
    _channel.sendGroup(RType::message::addComponent(_entity->getId(), "Health", new Haze::HealthData{50}, sizeof(Haze::HealthData)));
    _channel.sendGroup(RType::message::addComponent(_entity->getId(), "Position", new Haze::PositionData{pos->x, pos->y}, sizeof(Haze::PositionData)));
    _channel.sendGroup(RType::message::addComponent(_entity->getId(), "Velocity", new Haze::VelocityData{-1.5, 0}, sizeof(Haze::VelocityData)));
    _channel.sendGroup(RType::message::addComponent(_entity->getId(), "Scale", new Haze::ScaleData{3, 3}, sizeof(Haze::ScaleData)));
    _channel.sendGroup(RType::message::addComponent(_entity->getId(), "Hitbox", new Haze::HitboxData{5, 5, 33 - 10, 36 - 10}, sizeof(Haze::HitboxData)));
    _channel.sendGroup(RType::message::addComponent(_entity->getId(), "HitboxDisplay", nullptr, 0));
    _channel.sendGroup(RType::message::addComponent(_entity->getId(), "Sprite", new Haze::SpriteData{"assets/sprites/enemy.gif"}, sizeof(Haze::SpriteData)));
    _channel.sendGroup(RType::message::addComponent(_entity->getId(), "Animation", new Haze::AnimationData{"assets/AnimationJSON/enemy.json"}, sizeof(Haze::AnimationData)));
}

void Enemy::update()
{
    // clears the destroyed missiles from the vector
    bool invalidMissileExists = false;
    for (auto &missile: _missiles) {
        if (missile->_entity) {
            auto pos = dynamic_cast<Haze::Position *>(missile->_entity->getComponent("Position"));
            if (pos->x <= -50) {
                _channel.sendGroup(RType::message::deleteEntity(missile->_entity->getId()));
                missile->_entity->addComponent(new Haze::Destroy());
                missile->_entity = nullptr;
            }
        }
        if (!missile->_entity) {
            missile.reset();
            invalidMissileExists = true;
        }
    }
    if (invalidMissileExists)
        _missiles.erase(std::remove(_missiles.begin(), _missiles.end(), nullptr), _missiles.end());
}
