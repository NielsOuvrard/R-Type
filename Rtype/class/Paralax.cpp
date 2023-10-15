//
// Created by erwan on 10/15/23.
//

#include "Paralax.h"

Paralax::Paralax(Haze::Engine &engine, network::data_channel<protocol::data> &channel)
    : _engine(engine), _channel(channel)
{}

void Paralax::build()
{
    _bg1 = _engine.createEntity();
    _bg1->addComponent(new Haze::Position(0, 0));
    _bg1->addComponent(new Haze::Velocity(-0.8, 0));

    _bg2 = _engine.createEntity();
    _bg2->addComponent(new Haze::Position(562, 0));
    _bg2->addComponent(new Haze::Velocity(-0.8, 0));
    send();
}

void Paralax::update()
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

void Paralax::send()
{
    _channel.sendAll(RType::message::createEntity(_bg1->getId()));
    auto pos = dynamic_cast<Haze::Position *>(_bg1->getComponent("Position"));
    _channel.sendAll(RType::message::addComponent(_bg1->getId(), "Position", new Haze::PositionData{pos->x, pos->y}, sizeof(Haze::PositionData)));
    _channel.sendAll(RType::message::addComponent(_bg1->getId(), "Scale", new Haze::ScaleData{1.9, 1.9}, sizeof(Haze::ScaleData)));
    _channel.sendAll(RType::message::addComponent(_bg1->getId(), "Sprite", new Haze::SpriteData{"assets/sprites/space.jpg"}, sizeof(Haze::SpriteData)));

    _channel.sendAll(RType::message::createEntity(_bg2->getId()));
    pos = dynamic_cast<Haze::Position *>(_bg2->getComponent("Position"));
    _channel.sendAll(RType::message::addComponent(_bg2->getId(), "Position", new Haze::PositionData{pos->x, pos->y}, sizeof(Haze::PositionData)));
    _channel.sendAll(RType::message::addComponent(_bg2->getId(), "Scale", new Haze::ScaleData{1.9, 1.9}, sizeof(Haze::ScaleData)));
    _channel.sendAll(RType::message::addComponent(_bg2->getId(), "Sprite", new Haze::SpriteData{"assets/sprites/space.jpg"}, sizeof(Haze::SpriteData)));
}

void Paralax::sendUpdate()
{
    _channel.sendAll(RType::message::createEntity(_bg1->getId()));
    auto pos = dynamic_cast<Haze::Position *>(_bg1->getComponent("Position"));
    _channel.sendAll(RType::message::addComponent(_bg1->getId(), "Position", new Haze::PositionData{pos->x, pos->y}, sizeof(Haze::PositionData)));

    _channel.sendAll(RType::message::createEntity(_bg2->getId()));
    pos = dynamic_cast<Haze::Position *>(_bg2->getComponent("Position"));
    _channel.sendAll(RType::message::addComponent(_bg2->getId(), "Position", new Haze::PositionData{pos->x, pos->y}, sizeof(Haze::PositionData)));
}
