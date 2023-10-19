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

Wall::Wall(Haze::Engine &engine, network::data_channel<protocol::data> &channel, nlohmann::json dataJSON, float x, float y, bool isGround)
    : _engine(engine), _channel(channel), _dataJSON(std::move(dataJSON)), _x(x), _y(y), _isGround(isGround)
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
    _id = _entity->getId();
    std::cout << "["
              << _entity->getId()
              << "] Wall Created"
              << std::endl;
    _entity->addComponent(new Haze::Position(_x, _y));
    auto scale_y = (float)((_isGround ? -1.0 : 1.0) * 3.0);
    _entity->addComponent(new Haze::Scale(3, scale_y));
    _entity->addComponent(new Haze::Velocity(-5, 0, 0.05));

    std::map<std::string, Haze::Collision::CollisionInfo> mapCollision;
    mapCollision["player"] = {
            Haze::Collision::LAMBDA,
            0.1,
            [this](int a, int b) {
            }};
    _entity->addComponent(new Haze::Collision("wall", mapCollision));

    auto frame = _frames[_frameIndex];
    // _entity->addComponent(new Haze::Collision("wall", infos));
    _entity->addComponent(new Haze::Hitbox({{0, 0, frame.width, frame.height}}));
    send();
}

void Wall::send()
{
    auto frame = _frames[_frameIndex];

    _channel.sendGroup(RType::message::createEntity(_id));
    _channel.sendGroup(RType::message::addComponent(_id, "Position", new Haze::PositionData{_x, _y}, sizeof(Haze::PositionData)));
    _channel.sendGroup(RType::message::addComponent(_id, "Velocity", new Haze::VelocityData{-5, 0, 0.05}, sizeof(Haze::VelocityData)));
    auto scale_y = (float)((_isGround ? -1.0 : 1.0) * 3.0);
    _channel.sendGroup(RType::message::addComponent(_id, "Scale", new Haze::ScaleData{3, scale_y}, sizeof(Haze::ScaleData)));
    _channel.sendGroup(RType::message::addComponent(_id, "Hitbox", new Haze::HitboxData{{0, 0, frame.width, frame.height}}, sizeof(Haze::HitboxData)));
    _channel.sendGroup(RType::message::addComponent(_id, "Sprite", new Haze::SpriteData{"assets/sprites/wall.png"}, sizeof(Haze::SpriteData)));
    _channel.sendGroup(RType::message::addComponent(_id, "Animation", new Haze::AnimationData{"assets/AnimationJSON/ground.json"}, sizeof(Haze::AnimationData)));
    _channel.sendGroup(RType::message::addComponent(_id, "SpriteCropped", new Haze::SpriteCroppedData{_frameIndex}, sizeof(Haze::SpriteCroppedData)));
    _channel.sendGroup(RType::message::addComponent(_id, "HitboxDisplay", nullptr, 0));
}

void Wall::sendUpdate()
{
//    _channel.sendGroup(RType::message::addComponent(_id, "Position", new Haze::PositionData{_x, _y}, sizeof(Haze::PositionData)));
}
