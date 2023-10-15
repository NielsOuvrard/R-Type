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

#include "wall.hpp"
#include <haze-graphics.hpp>
#include <utility>

wall::wall(Haze::Engine &engine, network::data_channel<protocol::data> &channel, nlohmann::json dataJSON, float x, float y)
    : _engine(engine), _channel(channel), _dataJSON(std::move(dataJSON)), _x(x), _y(y)
    {

    // Create the frames
    nlohmann::json animation = _dataJSON["animation"];
    for (const auto &frame: animation) {
        _frames.emplace_back(Haze::Animation::intRect{frame["x"], frame["y"], frame["width"], frame["height"]});
    }
}

void wall::changeSpriteBack(Haze::Entity *E)
{
    idSprite = std::rand() % 10;
    _sheet = _jsonData["animation"][idSprite];
    auto Animation = static_cast<Haze::Animation *>(E->getComponent("Animation"));
    Animation->frames[0].x = _sheet["x"];
    Animation->frames[0].y = _sheet["y"];
    Animation->frames[0].width = _sheet["width"];
    Animation->frames[0].height = _sheet["height"];
}

void wall::build() {
    _entity = _engine.createEntity();
    _entity->addComponent(new Haze::Position(x, y));
    _entity->addComponent(new Haze::Scale(4, -4));
//    _entity->addComponent(new Haze::Velocity(1, 0));

    Haze::Collision::CollisionInfo collisionInfo = {
            Haze::Collision::LAMBDA,
            0.1,
            [this](int a, int b){
                std::cout << "Collide\n";
            }
    };
    std::map<std::string, Haze::Collision::CollisionInfo> infos = {
            {"player", collisionInfo},
    };
    auto hitbox = static_cast<Haze::Hitbox::intRect>(_frames[0]);
    _entity->addComponent(new Haze::Collision("wall", infos));
    _entity->addComponent(new Haze::Hitbox{hitbox});
    send();
}

void wall::update() {

}

void wall::send() {
    auto id = _entity.getId();
    auto pos = dynamic_cast<Haze::Position *>(_entity->getComponent("Position"));
    auto scale = dynamic_cast<Haze::Scale *>(_entity->getComponent("Scale"));
    auto hitbox = dynamic_cast<Haze::Hitbox *>(_entity->getComponent("Hitbox"))->hitbox.front();

    _channel.sendAll(RType::message::addComponent(id, "Position", new Haze::PositionData{pos->x, pos->y}, sizeof(Haze::PositionData)));
    _channel.sendAll(RType::message::addComponent(id, "Scale", new Haze::ScaleData{scale->x, scale->y}, sizeof(Haze::ScaleData)));
    _channel.sendAll(RType::message::addComponent(id, "Hitbox", new Haze::HitboxData{hitbox}, sizeof(Haze::HitboxData)));
    _channel.sendAll(RType::message::addComponent(id, "Sprite", new Haze::SpriteData{"assets/sprites/wall.png"}, sizeof(Haze::SpriteData)));
    _channel.sendAll(RType::message::addComponent(id, "Animation", new Haze::AnimationData{"assets/AnimationJSON/ground.json"}, sizeof(Haze::AnimationData)));
    _channel.sendAll(RType::message::addComponent(id, "SpriteCroped", new Haze::SpriteCropedData{idSprite},sizeof(Haze::SpriteCropedData)));
    _channel.sendAll(RType::message::addComponent(id, "HitboxDisplay", nullptr, 0));
    }
}

void wall::sendUpdate() {

}