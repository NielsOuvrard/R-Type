//
// Created by Niels Ouvrard on 29/10/2023.
//

#include "Boss.h"

Boss::Boss(DataGame dataGame, TypeEntities typeEntities, nlohmann::json data_from_map)
    : _dataGame(dataGame), _typeEntities(typeEntities)
{
    _data.x = data_from_map["x"];
    _data.y = data_from_map["y"];
    _type = data_from_map["type"];// TODO boss ID
    _next_shot_upper = false;
    _y_next_shot = 100;
}

void fill_data_from_boss(BossData &data, nlohmann::json jsonData)
{
    data.hitBoxData = {};
    data.tics = 0.05;
    data.damage = 10;
    data.life = 100;
    data.path_sprite = "";
    data.tools_path_sprite = "";
    data.tools_path_json = "";
    data.sound_spawn = "";
    data.sound_death = "";
    data.sound_damage = "";

    if (jsonData.contains("hitbox")) {
        if (jsonData["hitbox"].contains("x"))
            data.hitBoxData.x = jsonData["hitbox"]["x"];
        if (jsonData["hitbox"].contains("y"))
            data.hitBoxData.y = jsonData["hitbox"]["y"];
        if (jsonData["hitbox"].contains("width"))
            data.hitBoxData.width = jsonData["hitbox"]["width"];
        if (jsonData["hitbox"].contains("height"))
            data.hitBoxData.height = jsonData["hitbox"]["height"];
    }
    if (jsonData.contains("tics")) {
        data.tics = jsonData["tics"];
    }
    if (jsonData.contains("damage")) {
        data.damage = jsonData["damage"];
    }
    if (jsonData.contains("life")) {
        data.life = jsonData["life"];
    }
    if (jsonData.contains("path_sprite")) {
        data.path_sprite = jsonData["path_sprite"];
    }
    if (jsonData.contains("tools_path_sprite")) {
        data.tools_path_sprite = jsonData["tools_path_sprite"];
    }
    if (jsonData.contains("tools_path_json")) {
        data.tools_path_json = jsonData["tools_path_json"];
    }
    if (jsonData.contains("sound_spawn")) {
        data.sound_spawn = jsonData["sound_spawn"];
    }
    if (jsonData.contains("sound_death")) {
        data.sound_death = jsonData["sound_death"];
    }
    if (jsonData.contains("sound_damage")) {
        data.sound_damage = jsonData["sound_damage"];
    }
}

void Boss::build(std::string filePath)
{
    std::ifstream fileStream(filePath);
    if (fileStream.is_open()) {
        try {
            std::cout << "begin parsing file: " << filePath << std::endl;

            nlohmann::json jsonData;
            fileStream >> jsonData;
            fill_data_from_boss(_data, jsonData);
            _data.path_json = filePath;
        } catch (nlohmann::json::parse_error &e) {
            std::cerr << "Error parsing JSON file: " << filePath << std::endl;
            std::cerr << e.what() << std::endl;
        }

        fileStream.close();
    } else {
        std::cerr << "Failed to open file: " << filePath << std::endl;
    }

    std::chrono::milliseconds d((std::rand() % 10 + 5) * 1000);
    _missileCd.setDuration(d);

    _missileCd.Activate();

    _body = _dataGame.engine.createEntity();

    if (!_data.sound_spawn.empty()) {
        std::cout << "\033[1;34mplay spawn sound\033[0m" << std::endl;
        // create sound at the spawn
        auto elem_sound = new Haze::AnimationData();
        strncpy(elem_sound->path, _data.sound_spawn.c_str(), sizeof(elem_sound->path));
        elem_sound->path[sizeof(elem_sound->path) - 1] = '\0';
        _dataGame.channel.sendGroup(RType::message::addComponent(_body->getId(), "Audio", elem_sound, sizeof(Haze::AudioData)));
    }
    _body->addComponent(new Haze::Position(WINDOW_WIDTH + SIZE_TILE + _data.x, _data.y));
    _body->addComponent(new Haze::Velocity(VELOCITY_WALL_X, VELOCITY_WALL_Y, 0.05));
    _body->addComponent(new Haze::Scale(UNIVERSAL_SCALE, UNIVERSAL_SCALE));
    _body->addComponent(new Haze::Hitbox({{_data.hitBoxData.x, _data.hitBoxData.y, _data.hitBoxData.width, _data.hitBoxData.height}}));

    _tummy = _dataGame.engine.createEntity();
    _tummy->addComponent(new Haze::Position(WINDOW_WIDTH + SIZE_TILE + _data.x + (71 * UNIVERSAL_SCALE), _data.y + (96 * UNIVERSAL_SCALE)));
    _tummy->addComponent(new Haze::Velocity(VELOCITY_WALL_X, VELOCITY_WALL_Y, 0.05));
    _tummy->addComponent(new Haze::Scale(UNIVERSAL_SCALE, UNIVERSAL_SCALE));
    //    _tummy->addComponent(new Haze::Hitbox({{_data.hitBoxData.x, _data.hitBoxData.y, _data.hitBoxData.width, _data.hitBoxData.height}}));

    std::map<std::string, Haze::Collision::CollisionInfo> boss_collisions;
    boss_collisions["missile"] = {
            Haze::Collision::LAMBDA,
            0.1,
            [this](int a, int b) {
                //                if (!_body) {
                //                    return;
                //                }
                auto damage = dynamic_cast<Haze::Damage *>(_dataGame.engine.getEntity(b)->getComponent("Damage"));
                if (damage == nullptr) {
                    return;
                }
                if (_data.life == -1) {// immortal
                    return;
                }
                _data.life -= damage->damage;
                if (_data.life <= 0) {
                    if (!_data.sound_death.empty()) {
                        std::cout << "\033[1;34mplay death sound\033[0m" << std::endl;
                        // create sound at the death
                        auto elem_sound = new Haze::AnimationData();
                        strncpy(elem_sound->path, _data.sound_death.c_str(), sizeof(elem_sound->path));
                        elem_sound->path[sizeof(elem_sound->path) - 1] = '\0';
                        _dataGame.channel.sendGroup(RType::message::addComponent(_body->getId(), "Audio", elem_sound, sizeof(Haze::AudioData)));
                    }
                    _dataGame.channel.sendGroup(RType::message::addComponent(_tummy->getId(), "Audio", new Haze::AudioData{"assets/sounds/double_explo.wav"}, sizeof(Haze::AudioData)));
                    auto position = dynamic_cast<Haze::Position *>(_body->getComponent("Position"));
                    _data.x = position->x;
                    _data.y = position->y;
                    _dataGame.channel.sendGroup(RType::message::deleteEntity(_body->getId()));
                    _body->addComponent(new Haze::Destroy());
                    _body = nullptr;

                    _dataGame.channel.sendGroup(RType::message::deleteEntity(_tummy->getId()));
                    _tummy->addComponent(new Haze::Destroy());
                    _tummy = nullptr;

                    this->_isDead = true;
                } else {
                    if (!_data.sound_damage.empty()) {
                        // create sound at the death
                        auto elem_sound = new Haze::AnimationData();
                        strncpy(elem_sound->path, _data.sound_damage.c_str(), sizeof(elem_sound->path));
                        elem_sound->path[sizeof(elem_sound->path) - 1] = '\0';
                        _dataGame.channel.sendGroup(RType::message::addComponent(_body->getId(), "Audio", elem_sound, sizeof(Haze::AudioData)));
                    }
                    _dataGame.channel.sendGroup(RType::message::addComponent(_tummy->getId(), "Audio", new Haze::AudioData{"assets/sounds/little_explo.wav"}, sizeof(Haze::AudioData)));
                    _data.life -= damage->damage;
                }
            }};

    boss_collisions["player"] = {
            Haze::Collision::LAMBDA,
            0.1,
            [this](int a, int b) {
                if (!_body) {
                    return;
                }
                // nothing happened for the boss
            }};
    _body->addComponent(new Haze::Collision("enemy", boss_collisions));
    send();
}

void Boss::send()
{
    if (_body == nullptr || _tummy == nullptr) {
        return;
    }
    auto pos = dynamic_cast<Haze::Position *>(_body->getComponent("Position"));
    _dataGame.channel.sendGroup(RType::message::createEntity(_body->getId()));
    _dataGame.channel.sendGroup(RType::message::addComponent(_body->getId(), "Health", new Haze::HealthData{_data.life}, sizeof(Haze::HealthData)));
    _dataGame.channel.sendGroup(RType::message::addComponent(_body->getId(), "Position", new Haze::PositionData{pos->x, pos->y}, sizeof(Haze::PositionData)));
    _dataGame.channel.sendGroup(RType::message::addComponent(_body->getId(), "Velocity", new Haze::VelocityData{VELOCITY_WALL_X, VELOCITY_WALL_Y, 0.05}, sizeof(Haze::VelocityData)));
    _dataGame.channel.sendGroup(RType::message::addComponent(_body->getId(), "Scale", new Haze::ScaleData{UNIVERSAL_SCALE, UNIVERSAL_SCALE}, sizeof(Haze::ScaleData)));
    _dataGame.channel.sendGroup(RType::message::addComponent(_body->getId(), "Hitbox", new Haze::HitboxData{_data.hitBoxData.x, _data.hitBoxData.y, _data.hitBoxData.width, _data.hitBoxData.height}, sizeof(Haze::HitboxData)));
    //    _dataGame.channel.sendGroup(RType::message::addComponent(_body->getId(), "Hitbox", new Haze::HitboxData{_data.hitBoxData.x + 100, _data.hitBoxData.y + 100, _data.hitBoxData.width + 100, _data.hitBoxData.height + 100}, sizeof(Haze::HitboxData)));
    _dataGame.channel.sendGroup(RType::message::addComponent(_body->getId(), "HitboxDisplay", nullptr, 0));
    auto elem_sprite = new Haze::SpriteData();
    strncpy(elem_sprite->path, _data.path_sprite.c_str(), sizeof(elem_sprite->path));
    elem_sprite->path[sizeof(elem_sprite->path) - 1] = '\0';
    _dataGame.channel.sendGroup(RType::message::addComponent(_body->getId(), "Sprite", elem_sprite, sizeof(Haze::SpriteData)));

    auto elem_animation = new Haze::AnimationData();
    strncpy(elem_animation->path, _data.path_json.c_str(), sizeof(elem_animation->path));
    elem_animation->path[sizeof(elem_animation->path) - 1] = '\0';
    _dataGame.channel.sendGroup(RType::message::addComponent(_body->getId(), "Animation", elem_animation, sizeof(Haze::AnimationData)));


    auto tummy_pos = dynamic_cast<Haze::Position *>(_tummy->getComponent("Position"));
    _dataGame.channel.sendGroup(RType::message::createEntity(_tummy->getId()));
    _dataGame.channel.sendGroup(RType::message::addComponent(_tummy->getId(), "Health", new Haze::HealthData{_data.life}, sizeof(Haze::HealthData)));
    _dataGame.channel.sendGroup(RType::message::addComponent(_tummy->getId(), "Position", new Haze::PositionData{tummy_pos->x, tummy_pos->y}, sizeof(Haze::PositionData)));
    _dataGame.channel.sendGroup(RType::message::addComponent(_tummy->getId(), "Velocity", new Haze::VelocityData{VELOCITY_WALL_X, VELOCITY_WALL_Y, 0.05}, sizeof(Haze::VelocityData)));
    _dataGame.channel.sendGroup(RType::message::addComponent(_tummy->getId(), "Scale", new Haze::ScaleData{UNIVERSAL_SCALE, UNIVERSAL_SCALE}, sizeof(Haze::ScaleData)));
    _dataGame.channel.sendGroup(RType::message::addComponent(_tummy->getId(), "Hitbox", new Haze::HitboxData{_data.hitBoxData.x, _data.hitBoxData.y, _data.hitBoxData.width, _data.hitBoxData.height}, sizeof(Haze::HitboxData)));
    // _dataGame.channel.sendGroup(RType::message::addComponent(_tummy->getId(), "HitboxDisplay", nullptr, 0));
    auto tummy_sprite = new Haze::SpriteData();
    strncpy(tummy_sprite->path, _data.tools_path_sprite.c_str(), sizeof(tummy_sprite->path));
    tummy_sprite->path[sizeof(tummy_sprite->path) - 1] = '\0';
    _dataGame.channel.sendGroup(RType::message::addComponent(_tummy->getId(), "Sprite", tummy_sprite, sizeof(Haze::SpriteData)));

    auto tummy_animation = new Haze::AnimationData();
    strncpy(tummy_animation->path, _data.tools_path_json.c_str(), sizeof(tummy_animation->path));
    tummy_animation->path[sizeof(tummy_animation->path) - 1] = '\0';
    _dataGame.channel.sendGroup(RType::message::addComponent(_tummy->getId(), "Animation", tummy_animation, sizeof(Haze::AnimationData)));
}

void Boss::shot()
{
    if (_body == nullptr || _tummy == nullptr) {
        return;
    }
    if (_missiles.size() < 10 && !_dataGame.map_moving) {
        uint32_t random_pos_y = (std::rand() % 100);
        if ((_next_shot_upper && _y_next_shot > WINDOW_HEIGHT - 100) || (!_next_shot_upper && _y_next_shot < 100)) {
            _next_shot_upper = !_next_shot_upper;
        }

        auto position = dynamic_cast<Haze::Position *>(_body->getComponent("Position"));
        uint32_t type_shot_random = 1 + (std::rand() % (_typeEntities.shots.size()));
        _missiles.emplace_back(std::make_unique<Shot>(_dataGame, _typeEntities, type_shot_random, -1, 0, "enemy"));
        _missiles.back()->build(position->x + 100, _y_next_shot + random_pos_y);
        std::cout << "new shot in: " << position->x + 100 << " " << _y_next_shot + random_pos_y << std::endl;

        if (_next_shot_upper)
            _y_next_shot += random_pos_y;
        else
            _y_next_shot -= random_pos_y;
    }
}

void Boss::update()
{
    if (_body == nullptr || _tummy == nullptr) {
        return;
    }
    // clears the destroyed missiles from the vector
    bool invalidShotExists = false;
    for (auto &missile: _missiles) {
        if (!missile) {
            invalidShotExists = true;
            break;
        }
        if (missile->_entity) {
            auto pos = dynamic_cast<Haze::Position *>(missile->_entity->getComponent("Position"));

            if ((pos->x > WINDOW_WIDTH + 200 || pos->x < -100) || pos->y > WINDOW_HEIGHT + 100) {
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

void Boss::stopVelocity()
{
    if (_body == nullptr || _tummy == nullptr) {
        return;
    }
    _body->addComponent(new Haze::Velocity(0, 0, 0.5));// ? should delete this ?

    auto pos = dynamic_cast<Haze::Position *>(_body->getComponent("Position"));
    _dataGame.channel.sendGroup(RType::message::addComponent(_body->getId(), "Velocity", new Haze::VelocityData{0, 0, 0.5}, sizeof(Haze::VelocityData)));
    _dataGame.channel.sendGroup(RType::message::addComponent(_body->getId(), "Position", new Haze::PositionData{pos->x, pos->y}, sizeof(Haze::PositionData)));


    _tummy->addComponent(new Haze::Velocity(0, 0, 0.5));// ? should delete this ?

    auto pos_tummy = dynamic_cast<Haze::Position *>(_tummy->getComponent("Position"));
    _dataGame.channel.sendGroup(RType::message::addComponent(_tummy->getId(), "Velocity", new Haze::VelocityData{0, 0, 0.5}, sizeof(Haze::VelocityData)));
    _dataGame.channel.sendGroup(RType::message::addComponent(_tummy->getId(), "Position", new Haze::PositionData{pos_tummy->x, pos_tummy->y}, sizeof(Haze::PositionData)));
}
