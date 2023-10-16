/*
** ooooooooo.           ooooooooooooo
** `888   `Y88.         8'   888   `8
**  888   .d88'              888      oooo    ooo oo.ooooo.   .ooooo.
**  888ooo88P'               888       `88.  .8'   888' `88b d88' `88b
**  888`88b.    8888888      888        `88..8'    888   888 888ooo888
**  888  `88b.               888         `888'     888   888 888    .o
** o888o  o888o             o888o         .8'      888bod8P' `Y8bod8P'
**                                    .o..P'       888
**                                    `Y8P'       o888o
**
** Wall
*/

#include "Wall.hpp"
#include <haze-graphics.hpp>
#include <utility>

Wall::Wall(Haze::Engine &engine, network::data_channel<protocol::data> &channel, nlohmann::json dataJSON, float x, float y)
    : _engine(engine), _channel(channel), _dataJSON(std::move(dataJSON)), _x(x), _y(y)
{
    // Create the frames
    nlohmann::json animation = _dataJSON["animation"];
    for (const auto &frame: animation) {
        _frames.emplace_back(Haze::Animation::intRect{frame["x"], frame["y"], frame["width"], frame["height"]});
    }
}

void Wall::build(uint8_t frameIndex)
{
    _frameIndex = frameIndex;
    _entity = _engine.createEntity();
    _entity->addComponent(new Haze::Position(_x, _y));
    _entity->addComponent(new Haze::Scale(4, -4));
    //    _entity->addComponent(new Haze::Velocity(1, 0));

    Haze::Collision::CollisionInfo collisionInfo = {
            Haze::Collision::LAMBDA,
            0.1,
            [this](int a, int b) {
                std::cout << "Collision\n";
            }};
    std::map<std::string, Haze::Collision::CollisionInfo> infos = {
            {"player", collisionInfo},
    };

    auto frame = _frames[_frameIndex];
    _entity->addComponent(new Haze::Collision("wall", infos));
    _entity->addComponent(new Haze::Hitbox({{frame.x, frame.y, frame.width, frame.height}}));
    send();
}

void Wall::send()
{
    auto id = _entity->getId();
    auto pos = dynamic_cast<Haze::Position *>(_entity->getComponent("Position"));
    auto scale = dynamic_cast<Haze::Scale *>(_entity->getComponent("Scale"));
    auto hitbox = dynamic_cast<Haze::Hitbox *>(_entity->getComponent("Hitbox"))->hitbox.front();

    _channel.sendGroup(RType::message::createEntity(id));
    _channel.sendGroup(RType::message::addComponent(id, "Position", new Haze::PositionData{pos->x, pos->y}, sizeof(Haze::PositionData)));
    _channel.sendGroup(RType::message::addComponent(id, "Scale", new Haze::ScaleData{scale->x, scale->y}, sizeof(Haze::ScaleData)));
    _channel.sendGroup(RType::message::addComponent(id, "Hitbox", new Haze::HitboxData{hitbox}, sizeof(Haze::HitboxData)));
    _channel.sendGroup(RType::message::addComponent(id, "Sprite", new Haze::SpriteData{"assets/sprites/wall.png"}, sizeof(Haze::SpriteData)));
    _channel.sendGroup(RType::message::addComponent(id, "Animation", new Haze::AnimationData{"assets/AnimationJSON/ground.json"}, sizeof(Haze::AnimationData)));
    _channel.sendGroup(RType::message::addComponent(id, "SpriteCropped", new Haze::SpriteCroppedData{_frameIndex}, sizeof(Haze::SpriteCroppedData)));
    _channel.sendGroup(RType::message::addComponent(id, "HitboxDisplay", nullptr, 0));
}

void Wall::sendUpdate()
{
    auto id = _entity->getId();
    auto pos = dynamic_cast<Haze::Position *>(_entity->getComponent("Position"));
    _channel.sendGroup(RType::message::addComponent(id, "Position", new Haze::PositionData{pos->x, pos->y}, sizeof(Haze::PositionData)));
}
