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
    _entity = _engine.createEntity();
    std::cout << "["
              << _entity->getId()
              << "] Player Created"
              << std::endl;
    _entity->addComponent(new Haze::Velocity(0, 0));
    _entity->addComponent(new Haze::Position(100, 200));
    _entity->addComponent(new Haze::Scale(3, 3));
    _entity->addComponent(new Haze::Hitbox({{0, 0, 32, 14}}));
    _entity->addComponent(new Haze::OnKeyPressed(
            [this](int actor, std::vector<Haze::InputType> components) {
                if (IS_KEY_PRESSED(KEY_F) && _missileCd.IsReady()) {
                    _missileCd.Activate();
                    auto position = dynamic_cast<Haze::Position *>(this->_entity->getComponent("Position"));
                    _missiles.emplace_back(std::make_unique<Missile>(_engine, _channel, true));
                    _missiles.back()->build(position->x, position->y);
                }

                auto velocity = dynamic_cast<Haze::Velocity *>(_entity->getComponent("Velocity"));
                if (velocity == nullptr) {
                    _entity->addComponent(new Haze::Velocity(0, 0));
                    velocity = dynamic_cast<Haze::Velocity *>(_entity->getComponent("Velocity"));
                }
                velocity->x = 0;
                velocity->y = 0;

                if (IS_KEY_PRESSED(KEY_Z) || IS_KEY_PRESSED(KEY_UP_ARROW)) {
                    velocity->y += -10;
                    sendUpdate();
                }
                if (IS_KEY_PRESSED(KEY_Q) || IS_KEY_PRESSED(KEY_LEFT_ARROW)) {
                    velocity->x += -10;
                    sendUpdate();
                }
                if (IS_KEY_PRESSED(KEY_S) || IS_KEY_PRESSED(KEY_DOWN_ARROW)) {
                    velocity->y += 10;
                    sendUpdate();
                }
                if (IS_KEY_PRESSED(KEY_D) || IS_KEY_PRESSED(KEY_RIGHT_ARROW)) {
                    velocity->x += 10;
                    sendUpdate();
                }
            },
            _id));
    std::map<std::string, Haze::Collision::CollisionInfo> mapCollision;
    mapCollision["enemy"] = {
            Haze::Collision::LAMBDA,
            0.1,
            [this](int a, int b) {
                if (!_entity) {
                    return;
                }
                _hp -= 20;
                if (_hp <= 0) {
                    _channel.sendGroup(RType::message::deleteEntity(_entity->getId()));
                    _entity->addComponent(new Haze::Destroy());
                    _entity = nullptr;
                }
            }};
    mapCollision["missile-enemy"] = {
            Haze::Collision::LAMBDA,
            0.1,
            [this](int a, int b) {
                if (!_entity) {
                    return;
                }
                auto damage = dynamic_cast<Haze::Damage *>(_engine.getEntity(b)->getComponent("Damage"));
                _hp -= damage->damage;
                if (_hp <= 0) {
                    _channel.sendGroup(RType::message::deleteEntity(_entity->getId()));
                    _entity->addComponent(new Haze::Destroy());
                    _entity = nullptr;
                }
            }};
    _entity->addComponent(new Haze::Collision("player", mapCollision));
    send();
}

void Player::send()
{
    // TODO: Free allocated Data created with new
    auto pos = dynamic_cast<Haze::Position *>(_entity->getComponent("Position"));
    auto scale = dynamic_cast<Haze::Scale *>(_entity->getComponent("Scale"));
    auto hitbox = dynamic_cast<Haze::Hitbox *>(_entity->getComponent("Hitbox"))->hitbox.front();

    _channel.sendGroup(RType::message::createEntity(_entity->getId()));
    _channel.sendGroup(RType::message::addComponent(_entity->getId(), "Position", new Haze::PositionData{pos->x, pos->y}, sizeof(Haze::PositionData)));
    _channel.sendGroup(RType::message::addComponent(_entity->getId(), "Scale", new Haze::ScaleData{scale->x, scale->y}, sizeof(Haze::ScaleData)));
    _channel.sendGroup(RType::message::addComponent(_entity->getId(), "Hitbox", new Haze::HitboxData{hitbox}, sizeof(Haze::HitboxData)));
    _channel.sendGroup(RType::message::addComponent(_entity->getId(), "HitboxDisplay", nullptr, 0));
    _channel.sendGroup(RType::message::addComponent(_entity->getId(), "Sprite", new Haze::SpriteData{"assets/sprites/spaceships.png"}, sizeof(Haze::SpriteData)));
    if (_id == 1) {
        _channel.sendGroup(RType::message::addComponent(_entity->getId(), "Animation", new Haze::AnimationData{"assets/AnimationJSON/spaceship1.json"}, sizeof(Haze::AnimationData)));
    } else if (_id == 2) {
        _channel.sendGroup(RType::message::addComponent(_entity->getId(), "Animation", new Haze::AnimationData{"assets/AnimationJSON/spaceship2.json"}, sizeof(Haze::AnimationData)));
    } else if (_id == 3) {
        _channel.sendGroup(RType::message::addComponent(_entity->getId(), "Animation", new Haze::AnimationData{"assets/AnimationJSON/spaceship3.json"}, sizeof(Haze::AnimationData)));
    } else if (_id == 4) {
        _channel.sendGroup(RType::message::addComponent(_entity->getId(), "Animation", new Haze::AnimationData{"assets/AnimationJSON/spaceship4.json"}, sizeof(Haze::AnimationData)));
    }
}

void Player::sendUpdate()
{
    auto pos = dynamic_cast<Haze::Position *>(_entity->getComponent("Position"));
    _channel.sendGroup(RType::message::addComponent(_entity->getId(), "Position", new Haze::PositionData{pos->x, pos->y}, sizeof(Haze::PositionData)));
}

void Player::update()
{
    bool invalidMissileExists = false;
    for (auto &missile: _missiles) {
        if (missile->_entity) {
            auto pos = dynamic_cast<Haze::Position *>(missile->_entity->getComponent("Position"));
            if (pos->x >= 800) {
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
