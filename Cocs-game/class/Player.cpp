//
// Created by erwan on 10/15/23.
//

#include "Player.h"

#define IS_KEY_PRESSED(key) (std::find(components.begin(), components.end(), Haze::InputType::key) != components.end())

Player::Player(Haze::Engine &engine, network::data_channel<protocol::data> &channel, uint32_t id)
    : _engine(engine), _channel(channel), _id(id)
{
    // _scoreText = std::make_unique<element::TextInput>(engine, "0");
}

void Player::build()
{
    _entity = _engine.createEntity();
    _scoreEntity = _engine.createEntity();
    std::cout << "["
              << _entity->getId()
              << "] Player Created"
              << std::endl;
    _entity->addComponent(new Haze::Velocity(0, 0, 0.05));
    if (_id == 1) {
        _entity->addComponent(new Haze::Position(40, 300));
    } else if (_id == 2) {
        _entity->addComponent(new Haze::Position(730, 300));
    }
    _entity->addComponent(new Haze::Scale(2, 2));
    _entity->addComponent(new Haze::Hitbox({{0, 0, 20, 50}}));
    _entity->addComponent(new Haze::OnKeyPressed(
            [this](int actor, std::vector<Haze::InputType> components) {
                auto position = dynamic_cast<Haze::Position *>(_entity->getComponent("Position"));
                for (auto &component: components) {
                    if (component == Haze::InputType::KEY_Z) {
                        position->y += -10;
                    }
                    if (component == Haze::InputType::KEY_S) {
                        position->y += 10;
                    }
                }
                sendUpdate();
            },
            _id));
    std::map<std::string, Haze::Collision::CollisionInfo> mapCollision;
    mapCollision["ball"] = {
            Haze::Collision::LAMBDA,
            0.3,
            [this](int a, int b) {
                if (!_entity) {
                    return;
                }
            }};
    _entity->addComponent(new Haze::Collision("player", mapCollision));
    // _scoreText->getEntity().addComponent(new Haze::Position(400, 50));
    send();
}

void Player::send()
{
    // TODO: Free allocated Data created with new
    auto pos = dynamic_cast<Haze::Position *>(_entity->getComponent("Position"));
    auto scale = dynamic_cast<Haze::Scale *>(_entity->getComponent("Scale"));
    auto hitbox = dynamic_cast<Haze::Hitbox *>(_entity->getComponent("Hitbox"))->hitbox.front();

    _channel.sendGroup(cocs_game::message::createEntity(_entity->getId()));
    _channel.sendGroup(cocs_game::message::addComponent(_entity->getId(), "Position", new Haze::PositionData{pos->x, pos->y}, sizeof(Haze::PositionData)));
    _channel.sendGroup(cocs_game::message::addComponent(_entity->getId(), "Scale", new Haze::ScaleData{scale->x, scale->y}, sizeof(Haze::ScaleData)));
    _channel.sendGroup(cocs_game::message::addComponent(_entity->getId(), "Hitbox", new Haze::HitboxData{hitbox}, sizeof(Haze::HitboxData)));
    _channel.sendGroup(cocs_game::message::addComponent(_entity->getId(), "HitboxDisplay", nullptr, 0));
    _channel.sendGroup(cocs_game::message::addComponent(_entity->getId(), "Sprite", new Haze::SpriteData{"assets/sprites/player_pong.png"}, sizeof(Haze::SpriteData)));

    _channel.sendGroup(cocs_game::message::createEntity(_scoreEntity->getId()));
    if (_id == 1) {
        _channel.sendGroup(cocs_game::message::addComponent(_scoreEntity->getId(), "Position", new Haze::PositionData{600, 50}, sizeof(Haze::PositionData)));
    } else if (_id == 2) {
        _channel.sendGroup(cocs_game::message::addComponent(_scoreEntity->getId(), "Position", new Haze::PositionData{200, 50}, sizeof(Haze::PositionData)));
    }
    _channel.sendGroup(cocs_game::message::addComponent(_scoreEntity->getId(), "Scale", new Haze::ScaleData{1, 1}, sizeof(Haze::ScaleData)));
    auto txt = new Haze::TextData{"", 255, 255, 255, 255, "NotoMono.ttf"};
    std::strcat(txt->text, std::to_string(_score).data());
    _channel.sendGroup(cocs_game::message::addComponent(_scoreEntity->getId(), "Text", txt, sizeof(Haze::TextData)));
}

void Player::sendUpdate()
{
    auto pos = dynamic_cast<Haze::Position *>(_entity->getComponent("Position"));
    _channel.sendGroup(cocs_game::message::addComponent(_entity->getId(), "Position", new Haze::PositionData{pos->x, pos->y}, sizeof(Haze::PositionData)));
    std::cout << "send update player" << std::endl;
}

void Player::changeScore()
{
    _score++;
    send();
    std::cout << "Player " << _id << " score: " << _score << std::endl;
}

void Player::update()
{
}
