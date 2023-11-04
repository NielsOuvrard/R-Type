//
// Created by erwan on 10/15/23.
//

#include "Parallax.h"

Parallax::Parallax(DataGame dataGame)
    : _dataGame(dataGame), _bg1(nullptr), _bg2(nullptr)
{}

void Parallax::build(std::string parallax_path)
{
    _parallax_path = parallax_path;
    _bg1 = _dataGame.engine.createEntity();
    std::cout << "["
              << _bg1->getId()
              << "] Background 1 Created"
              << std::endl;
    _bg1->addComponent(new Haze::Position(0, 0));
    _bg1->addComponent(new Haze::Velocity(-0.8, 0, 0.1));

    _bg2 = _dataGame.engine.createEntity();
    std::cout << "["
              << _bg2->getId()
              << "] Background 2 Created"
              << std::endl;
    _bg2->addComponent(new Haze::Position(562, 0));
    _bg2->addComponent(new Haze::Velocity(-0.8, 0, 0.1));
    send();
}

void Parallax::update()
{
    auto pos1 = dynamic_cast<Haze::Position *>(_bg1->getComponent("Position"));
    auto pos2 = dynamic_cast<Haze::Position *>(_bg2->getComponent("Position"));
    if (pos1->x + 562 < 0) {
        pos1->x = 562;
        sendUpdate();
    }
    if (pos2->x + 562 < 0) {
        pos2->x = 562;
        sendUpdate();
    }
}

void Parallax::send()
{
    if (_parallax_path.empty()) {
        return;
    }

    auto elem_sprite = new Haze::SpriteData();
    strncpy(elem_sprite->path, _parallax_path.c_str(), sizeof(elem_sprite->path));
    elem_sprite->path[sizeof(elem_sprite->path) - 1] = '\0';
    auto elem_sprite_2 = new Haze::SpriteData();
    strncpy(elem_sprite_2->path, _parallax_path.c_str(), sizeof(elem_sprite_2->path));
    elem_sprite_2->path[sizeof(elem_sprite_2->path) - 1] = '\0';

    _dataGame.channel.sendGroup(RType::message::createEntity(_bg1->getId()));
    auto pos = dynamic_cast<Haze::Position *>(_bg1->getComponent("Position"));
    _dataGame.channel.sendGroup(RType::message::addComponent(_bg1->getId(), "Position", new Haze::PositionData{pos->x, pos->y}, sizeof(Haze::PositionData)));
    _dataGame.channel.sendGroup(RType::message::addComponent(_bg1->getId(), "Scale", new Haze::ScaleData{1.9, 1.9}, sizeof(Haze::ScaleData)));
    _dataGame.channel.sendGroup(RType::message::addComponent(_bg1->getId(), "Sprite", elem_sprite_2, sizeof(Haze::SpriteData)));
    _dataGame.channel.sendGroup(RType::message::addComponent(_bg1->getId(), "Velocity", new Haze::VelocityData{-0.8, 0, 0.1}, sizeof(Haze::VelocityData)));

    _dataGame.channel.sendGroup(RType::message::addComponent(_bg1->getId(), "Audio", new Haze::AudioData{"assets/sounds/ambiance.ogg"}, sizeof(Haze::AudioData)));

    _dataGame.channel.sendGroup(RType::message::createEntity(_bg2->getId()));
    pos = dynamic_cast<Haze::Position *>(_bg2->getComponent("Position"));
    _dataGame.channel.sendGroup(RType::message::addComponent(_bg2->getId(), "Velocity", new Haze::VelocityData{-0.8, 0, 0.1}, sizeof(Haze::VelocityData)));
    _dataGame.channel.sendGroup(RType::message::addComponent(_bg2->getId(), "Position", new Haze::PositionData{pos->x, pos->y}, sizeof(Haze::PositionData)));
    _dataGame.channel.sendGroup(RType::message::addComponent(_bg2->getId(), "Scale", new Haze::ScaleData{1.9, 1.9}, sizeof(Haze::ScaleData)));
    _dataGame.channel.sendGroup(RType::message::addComponent(_bg2->getId(), "Sprite", elem_sprite, sizeof(Haze::SpriteData)));
}

void Parallax::sendUpdate()
{
    auto pos = dynamic_cast<Haze::Position *>(_bg1->getComponent("Position"));
    _dataGame.channel.sendGroup(RType::message::addComponent(_bg1->getId(), "Position", new Haze::PositionData{pos->x, pos->y}, sizeof(Haze::PositionData)));

    pos = dynamic_cast<Haze::Position *>(_bg2->getComponent("Position"));
    _dataGame.channel.sendGroup(RType::message::addComponent(_bg2->getId(), "Position", new Haze::PositionData{pos->x, pos->y}, sizeof(Haze::PositionData)));
}
