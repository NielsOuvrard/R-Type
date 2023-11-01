//
// Created by erwan on 10/15/23.
//

#include "Parallax.h"

Parallax::Parallax(DataGame dataGame)
    : _dataGame(dataGame), _bg1(nullptr), _bg2(nullptr)
{}

void Parallax::build()
{
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
    }
    if (pos2->x + 562 < 0) {
        pos2->x = 562;
    }
}

void Parallax::send()
{
    _dataGame.channel.sendGroup(RType::message::createEntity(_bg1->getId()));
    auto pos = dynamic_cast<Haze::Position *>(_bg1->getComponent("Position"));
    _dataGame.channel.sendGroup(RType::message::addComponent(_bg1->getId(), "Position", new Haze::PositionData{pos->x, pos->y}, sizeof(Haze::PositionData)));
    _dataGame.channel.sendGroup(RType::message::addComponent(_bg1->getId(), "Scale", new Haze::ScaleData{1.9, 1.9}, sizeof(Haze::ScaleData)));
    _dataGame.channel.sendGroup(RType::message::addComponent(_bg1->getId(), "Sprite", new Haze::SpriteData{"assets/sprites/space.jpg"}, sizeof(Haze::SpriteData)));

    _dataGame.channel.sendGroup(RType::message::createEntity(_bg2->getId()));
    pos = dynamic_cast<Haze::Position *>(_bg2->getComponent("Position"));
    _dataGame.channel.sendGroup(RType::message::addComponent(_bg2->getId(), "Position", new Haze::PositionData{pos->x, pos->y}, sizeof(Haze::PositionData)));
    _dataGame.channel.sendGroup(RType::message::addComponent(_bg2->getId(), "Scale", new Haze::ScaleData{1.9, 1.9}, sizeof(Haze::ScaleData)));
    _dataGame.channel.sendGroup(RType::message::addComponent(_bg2->getId(), "Sprite", new Haze::SpriteData{"assets/sprites/space.jpg"}, sizeof(Haze::SpriteData)));
}

void Parallax::sendUpdate()
{
    auto pos = dynamic_cast<Haze::Position *>(_bg1->getComponent("Position"));
    _dataGame.channel.sendGroup(RType::message::addComponent(_bg1->getId(), "Position", new Haze::PositionData{pos->x, pos->y}, sizeof(Haze::PositionData)));

    pos = dynamic_cast<Haze::Position *>(_bg2->getComponent("Position"));
    _dataGame.channel.sendGroup(RType::message::addComponent(_bg2->getId(), "Position", new Haze::PositionData{pos->x, pos->y}, sizeof(Haze::PositionData)));
}
