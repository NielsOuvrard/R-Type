//
// Created by erwan on 10/15/23.
//

#include "Player.h"

#define IS_KEY_PRESSED(key) (std::find(components.begin(), components.end(), Haze::InputType::key) != components.end())

Player::Player(DataGame dataGame, TypeEntities typeEntities, uint32_t id)
    : _dataGame(dataGame), _typeEntities(typeEntities), _id(id)
{
}

void Player::build()
{
    _entity = _dataGame.engine.createEntity();
    std::cout << "["
              << _entity->getId()
              << "] Player Created"
              << std::endl;
    _entity->addComponent(new Haze::Velocity(0, 0, 0.05));
    _entity->addComponent(new Haze::Position(100, 300));
    _entity->addComponent(new Haze::Scale(UNIVERSAL_SCALE, UNIVERSAL_SCALE));
    _entity->addComponent(new Haze::Hitbox({{0, 0, 32, 14}}));
    _entity->addComponent(new Haze::OnKeyPressed(
            [this](int actor, std::vector<Haze::InputType> components) {
                if (IS_KEY_PRESSED(KEY_F) && _missileCd.IsReady()) {
                    _missileCd.Activate();
                    auto position = dynamic_cast<Haze::Position *>(this->_entity->getComponent("Position"));
                    _missiles.emplace_back(std::make_unique<Shot>(_dataGame, _typeEntities, 1, 1, 0, "player"));
                    _missiles.back()->build(position->x + (20 * UNIVERSAL_SCALE), position->y);
                }
                if (IS_KEY_PRESSED(KEY_E) && _missileCd.IsReady()) {
                    _missileCd.Activate();
                    auto position = dynamic_cast<Haze::Position *>(this->_entity->getComponent("Position"));
                    _missiles.emplace_back(std::make_unique<Shot>(_dataGame, _typeEntities, 3, 1, 0, "player"));
                    _missiles.back()->build(position->x + (20 * UNIVERSAL_SCALE), position->y);
                }
                auto position = dynamic_cast<Haze::Position *>(_entity->getComponent("Position"));

                for (auto &component: components) {
                    if (component == Haze::InputType::KEY_Z) {
                        position->y += -10;
                    }
                    if (component == Haze::InputType::KEY_Q) {
                        position->x += -10;
                    }
                    if (component == Haze::InputType::KEY_S) {
                        position->y += 10;
                    }
                    if (component == Haze::InputType::KEY_D) {
                        position->x += 10;
                    }
                }
                sendUpdate();
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
                int damage = 20;
                std::cout << "enemy die by touching player (player side)\n";
                std::cout << "hp = " << _hp << " - " << damage << " = " << _hp - damage << std::endl;
                _hp -= 20;
                if (_hp <= 0) {
                    _dataGame.channel.sendGroup(RType::message::addComponent(_entity->getId(), "Audio", new Haze::AudioData{"assets/sounds/double_explo.wav"}, sizeof(Haze::AudioData)));
                    _dataGame.channel.sendGroup(RType::message::deleteEntity(_entity->getId()));
                    _entity->addComponent(new Haze::Destroy());
                    _entity = nullptr;
                } else {
                    _dataGame.channel.sendGroup(RType::message::addComponent(_entity->getId(), "Audio", new Haze::AudioData{"assets/sounds/little_explo.wav"}, sizeof(Haze::AudioData)));
                    _hp -= damage;
                }
            }};
    mapCollision["missile-enemy"] = {
            Haze::Collision::LAMBDA,
            0.1,
            [this](int a, int b) {
                if (!_entity) {
                    return;
                }
                auto damage = dynamic_cast<Haze::Damage *>(_dataGame.engine.getEntity(b)->getComponent("Damage"));
                _hp -= damage->damage;
                if (_hp <= 0) {
                    _dataGame.channel.sendGroup(RType::message::addComponent(_entity->getId(), "Audio", new Haze::AudioData{"assets/sounds/double_explo.wav"}, sizeof(Haze::AudioData)));
                    _dataGame.channel.sendGroup(RType::message::deleteEntity(_entity->getId()));
                    _entity->addComponent(new Haze::Destroy());
                    _entity = nullptr;
                } else {
                    _dataGame.channel.sendGroup(RType::message::addComponent(_entity->getId(), "Audio", new Haze::AudioData{"assets/sounds/little_explo.wav"}, sizeof(Haze::AudioData)));
                    _hp -= damage->damage;
                }
            }};
    mapCollision["wall"] = {
            Haze::Collision::LAMBDA,
            0.1,
            [this](int a, int b) {
                if (!_entity) {
                    return;
                }
                _dataGame.channel.sendGroup(RType::message::addComponent(_entity->getId(), "Audio", new Haze::AudioData{"assets/sounds/double_explo.wav"}, sizeof(Haze::AudioData)));
                _dataGame.channel.sendGroup(RType::message::deleteEntity(_entity->getId()));
                _entity->addComponent(new Haze::Destroy());
                _entity = nullptr;
            }};
    mapCollision["boss"] = {
            Haze::Collision::LAMBDA,
            0.1,
            [this](int a, int b) {
                std::cout << "\033[1;34mplayer-boss\033[0m" << std::endl;
                if (!_entity) {
                    return;
                }
                _dataGame.channel.sendGroup(RType::message::deleteEntity(_entity->getId()));
                _entity->addComponent(new Haze::Destroy());
                _entity = nullptr;
            }};
    _entity->addComponent(new Haze::Collision("player", mapCollision));
    send();
}

void Player::send()
{
    // TODO: Free allocated Data created with new
    auto pos = dynamic_cast<Haze::Position *>(_entity->getComponent("Position"));
    //auto scale = dynamic_cast<Haze::Scale *>(_entity->getComponent("Scale"));
    auto hitbox = dynamic_cast<Haze::Hitbox *>(_entity->getComponent("Hitbox"))->hitbox.front();

    _dataGame.channel.sendGroup(RType::message::createEntity(_entity->getId()));
    _dataGame.channel.sendGroup(RType::message::addComponent(_entity->getId(), "Position", new Haze::PositionData{pos->x, pos->y}, sizeof(Haze::PositionData)));
    _dataGame.channel.sendGroup(RType::message::addComponent(_entity->getId(), "Scale", new Haze::ScaleData{UNIVERSAL_SCALE, UNIVERSAL_SCALE}, sizeof(Haze::ScaleData)));
    _dataGame.channel.sendGroup(RType::message::addComponent(_entity->getId(), "Hitbox", new Haze::HitboxData{hitbox}, sizeof(Haze::HitboxData)));
    _dataGame.channel.sendGroup(RType::message::addComponent(_entity->getId(), "Interpolation", new Haze::InterpolationData{_dataGame.engine.getFramerate()}, sizeof(Haze::InterpolationData)));
    //_dataGame.channel.sendGroup(RType::message::addComponent(_entity->getId(), "HitboxDisplay", nullptr, 0));
    _dataGame.channel.sendGroup(RType::message::addComponent(_entity->getId(), "Sprite", new Haze::SpriteData{"assets/sprites/spaceships.png"}, sizeof(Haze::SpriteData)));
    if (_id == 1) {
        _dataGame.channel.sendGroup(RType::message::addComponent(_entity->getId(), "Animation", new Haze::AnimationData{"assets/json_files/spaceship1.json"}, sizeof(Haze::AnimationData)));
    } else if (_id == 2) {
        _dataGame.channel.sendGroup(RType::message::addComponent(_entity->getId(), "Animation", new Haze::AnimationData{"assets/json_files/spaceship2.json"}, sizeof(Haze::AnimationData)));
    } else if (_id == 3) {
        _dataGame.channel.sendGroup(RType::message::addComponent(_entity->getId(), "Animation", new Haze::AnimationData{"assets/json_files/spaceship3.json"}, sizeof(Haze::AnimationData)));
    } else if (_id == 4) {
        _dataGame.channel.sendGroup(RType::message::addComponent(_entity->getId(), "Animation", new Haze::AnimationData{"assets/json_files/spaceship4.json"}, sizeof(Haze::AnimationData)));
    }
}

void Player::sendUpdate()
{
    auto pos = dynamic_cast<Haze::Position *>(_entity->getComponent("Position"));
    _dataGame.channel.sendGroup(RType::message::addComponent(_entity->getId(), "Position", new Haze::PositionData{pos->x, pos->y}, sizeof(Haze::PositionData)));
    std::cout << "send update player" << std::endl;
}

void Player::update()
{
    bool invalidShotExists = false;
    for (auto &missile: _missiles) {
        if (!missile) {
            invalidShotExists = true;
            return;
        }
        if (missile->_entity) {
            auto pos = dynamic_cast<Haze::Position *>(missile->_entity->getComponent("Position"));
            if ((pos->x > WINDOW_WIDTH + 100 || pos->x < -100) || pos->y > WINDOW_HEIGHT + 100) {
                std::cout << "\033[1;34mShot deleted\033[0m" << std::endl;
                _dataGame.channel.sendGroup(RType::message::deleteEntity(missile->_entity->getId()));
                missile->_entity->addComponent(new Haze::Destroy());
                missile->_entity = nullptr;
                invalidShotExists = true;
            }
        }
        if (!missile->_entity) {
            missile.reset();
        }
    }
    if (invalidShotExists)
        _missiles.erase(std::remove(_missiles.begin(), _missiles.end(), nullptr), _missiles.end());
}
