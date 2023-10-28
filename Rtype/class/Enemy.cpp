//
// Created by erwan on 10/15/23.
//

#include "Enemy.h"

#include <utility>

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

void fill_data_from_map(EnemyData &data, nlohmann::json jsonData)
{
    data.x = 0;
    data.y = 0;
    data.velocity_x = 0;
    data.velocity_y = 0;
    data.move = "linear";
    data.move_radius = -1;
    data.move_frequency = -1;
    data.move_amplitude = -1;
    data.move_time = -1;
    data.move_x = 0;

    if (jsonData.contains("x")) {
        data.x = jsonData["x"];
    }
    if (jsonData.contains("y")) {
        data.y = jsonData["y"];
    }
    if (jsonData.contains("velocity_y")) {
        data.velocity_y = jsonData["velocity_y"];
    }
    if (jsonData.contains("velocity_x")) {
        data.velocity_x = jsonData["velocity_x"];
    }
    if (jsonData.contains("move")) {
        data.move = jsonData["move"];
    }
    if (jsonData.contains("move_radius")) {
        data.move_radius = jsonData["move_radius"];
    }
    if (jsonData.contains("move_frequency")) {
        data.move_frequency = jsonData["move_frequency"];
    }
    if (jsonData.contains("move_amplitude")) {
        data.move_amplitude = jsonData["move_amplitude"];
    }
    if (jsonData.contains("move_time")) {
        data.move_time = jsonData["move_time"];
    }
    if (jsonData.contains("move_x")) {
        data.move_x = jsonData["move_x"];
    }
}

void Enemy::build(EnemyData data_enemy, nlohmann::json mapData)
{
    // * copy all data from type
    _data = std::move(data_enemy);
    // * copy all data from map
    fill_data_from_map(_data, mapData);
    //    _data.velocity_x -= VELOCITY_WALL_X;// ? not sure about this
    std::chrono::milliseconds d((std::rand() % 10 + 5) * 1000);
    _missileCd.setDuration(d);

    _missileCd.Activate();
    _entity = _engine.createEntity();
    std::cout << "[" << _entity->getId() << "] Enemy Created" << std::endl;
    _entity->addComponent(new Haze::Position(800 + _data.x, _data.y));// ? check if 800 is exactly the good tile
    _entity->addComponent(new Haze::Velocity(_data.velocity_x, _data.velocity_y, _data.move_time));

    if (_data.move == "sinusoidal" && _data.move_time != -1 && _data.move_amplitude != -1 && _data.move_frequency != -1) {
        _entity->addComponent(new Haze::SinVelocity(_data.move_x, _data.move_time, _data.move_amplitude, _data.move_frequency));
    }

    else if (_data.move == "circular" && _data.move_radius != -1 && _data.move_time != -1) {
        _entity->addComponent(new Haze::CircleVelocity(_data.move_x, _data.move_time, _data.move_radius));
    }

    _entity->addComponent(new Haze::Scale(UNIVERSAL_SCALE, UNIVERSAL_SCALE));
    _entity->addComponent(new Haze::Hitbox({{_data.hitBoxData.x, _data.hitBoxData.y, _data.hitBoxData.width, _data.hitBoxData.height}}));

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
                _data.life -= damage->damage;
                if (_data.life <= 0) {
                    auto position = dynamic_cast<Haze::Position *>(_entity->getComponent("Position"));
                    _data.x = position->x;
                    _data.y = position->y;
                    std::cout << "enemy die by missile player\n";
                    _channel.sendGroup(RType::message::deleteEntity(_entity->getId()));
                    _entity->addComponent(new Haze::Destroy());
                    _entity = nullptr;
                    this->_isDead = true;
                } else {
                    std::cout << "enemy damage by missile player: " << damage->damage << " hp: " << _data.life << "\n";
                    _data.life -= damage->damage;
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
    _channel.sendGroup(RType::message::addComponent(_entity->getId(), "Health", new Haze::HealthData{_data.life}, sizeof(Haze::HealthData)));
    _channel.sendGroup(RType::message::addComponent(_entity->getId(), "Position", new Haze::PositionData{pos->x, pos->y}, sizeof(Haze::PositionData)));
    _channel.sendGroup(RType::message::addComponent(_entity->getId(), "Velocity", new Haze::VelocityData{_data.velocity_x, _data.velocity_y, _data.move_time}, sizeof(Haze::VelocityData)));

    if (_data.move == "sinusoidal") {
        _channel.sendGroup(RType::message::addComponent(_entity->getId(), "SinVelocity", new Haze::SinVelocityData{_data.move_x, _data.move_time, _data.move_amplitude, _data.move_frequency}, sizeof(Haze::SinVelocityData)));
    } else if (_data.move == "circular") {
        _channel.sendGroup(RType::message::addComponent(_entity->getId(), "CircleVelocity", new Haze::CircleVelocityData{_data.move_x, _data.move_time, _data.move_radius}, sizeof(Haze::CircleVelocityData)));
    }
    _channel.sendGroup(RType::message::addComponent(_entity->getId(), "Scale", new Haze::ScaleData{UNIVERSAL_SCALE, UNIVERSAL_SCALE}, sizeof(Haze::ScaleData)));
    _channel.sendGroup(RType::message::addComponent(_entity->getId(), "Hitbox", new Haze::HitboxData{_data.hitBoxData.x, _data.hitBoxData.y, _data.hitBoxData.width, _data.hitBoxData.height}, sizeof(Haze::HitboxData)));
    //_channel.sendGroup(RType::message::addComponent(_entity->getId(), "HitboxDisplay", nullptr, 0));
    _channel.sendGroup(RType::message::addComponent(_entity->getId(), "Sprite", new Haze::SpriteData{"assets/sprites/enemy.gif"}, sizeof(Haze::SpriteData)));
    _channel.sendGroup(RType::message::addComponent(_entity->getId(), "Animation", new Haze::AnimationData{"assets/enemies/red_fly.json"}, sizeof(Haze::AnimationData)));
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
