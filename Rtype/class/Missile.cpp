//
// Created by erwan on 10/15/23.
//

#include "Missile.h"

Missile::Missile(Haze::Engine &engine, network::data_channel<protocol::data> &channel, Haze::Position *pos)
    : _engine(engine), _channel(channel), _pos(pos)
{
}

void Missile::build()
{
    entity = _engine.createEntity();
    Haze::Position *position = _pos;
    if (_pos == nullptr) {
        position = new Haze::Position(0, 0);
    }
    entity->addComponent(new Haze::Position(position->x + 28, position->y));
    entity->addComponent(new Haze::Velocity(2, 0));
    entity->addComponent(new Haze::Scale(3, 3));
    // TODO: Add lifetime to missile
    send();
}

void Missile::send()
{
    auto position = dynamic_cast<Haze::Position *>(entity->getComponent("Position"));
    _channel.sendAll(RType::message::createEntity(entity->getId()));
    _channel.sendAll(RType::message::addComponent(entity->getId(), "Position", new Haze::PositionData{position->x + 33 * 3, position->y}, sizeof(Haze::PositionData)));
    _channel.sendAll(RType::message::addComponent(entity->getId(), "Scale", new Haze::ScaleData{3, 3}, sizeof(Haze::ScaleData)));
    _channel.sendAll(RType::message::addComponent(entity->getId(), "Hitbox", new Haze::HitboxData({0, 0, 32, 14}), sizeof(Haze::HitboxData)));
    _channel.sendAll(RType::message::addComponent(entity->getId(), "HitboxDisplay", nullptr, 0));
    _channel.sendAll(RType::message::addComponent(entity->getId(), "Velocity", new Haze::VelocityData{2, 0}, sizeof(Haze::VelocityData)));
    _channel.sendAll(RType::message::addComponent(entity->getId(), "Sprite", new Haze::SpriteData{"assets/sprites/shot.png"}, sizeof(Haze::SpriteData)));
    _channel.sendAll(RType::message::addComponent(entity->getId(), "Animation", new Haze::AnimationData{"assets/AnimationJSON/shot.json"}, sizeof(Haze::AnimationData)));
    _channel.sendAll(RType::message::addComponent(entity->getId(), "SpriteCropped", new Haze::SpriteCroppedData{2}, sizeof(Haze::SpriteCroppedData)));
}
