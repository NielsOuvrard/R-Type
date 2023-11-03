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

#include "Wall.h"

Wall::Wall(DataGame dataGame, nlohmann::json dataJSON, float x, float y, bool isGround, std::string wall_json_path)
    : _dataGame(dataGame), _dataJSON(std::move(dataJSON)), _x(x), _y(y), _isGround(isGround), _wall_json_path(std::move(wall_json_path))
{
    // Create the frames
    nlohmann::json animation = _dataJSON["animation"];
    for (const auto &frame: animation) {
        _frames.emplace_back(Haze::Animation::intRect{frame["x"], frame["y"], frame["width"], frame["height"]});
    }
    std::cout << "frame size = " << _frames.size() << "\n";
}

void Wall::build(uint16_t frameIndex)
{
    _frameIndex = frameIndex;
    _entity = _dataGame.engine.createEntity();
    _id = _entity->getId();
    std::cout << "["
              << _entity->getId()
              << "] Wall Created"
              << std::endl;
    _entity->addComponent(new Haze::Position(_x, _y));
    auto scale_y = (float) ((_isGround ? -1.0 : 1.0) * UNIVERSAL_SCALE);
    _entity->addComponent(new Haze::Scale(UNIVERSAL_SCALE, scale_y));
    _entity->addComponent(new Haze::Velocity(VELOCITY_WALL_X, VELOCITY_WALL_Y, VELOCITY_WALL_TIME));

    std::map<std::string, Haze::Collision::CollisionInfo> mapCollision;
    mapCollision["player"] = {
            Haze::Collision::LAMBDA,
            0.1,
            [this](int a, int b) {
            }};
    _entity->addComponent(new Haze::Collision("wall", mapCollision));
    std::cout << "Collision OK\n";

    auto frame = _frames[_frameIndex];
    // _entity->addComponent(new Haze::Collision("wall", infos));
    _entity->addComponent(new Haze::Hitbox({{0, 0, frame.width, frame.height}}));
    send();
    std::cout << "Wall created end\n";
}

void Wall::send()
{
    auto frame = _frames[_frameIndex];

    _dataGame.channel.sendGroup(RType::message::createEntity(_id));
    _dataGame.channel.sendGroup(RType::message::addComponent(_id, "Position", new Haze::PositionData{_x, _y}, sizeof(Haze::PositionData)));
    _dataGame.channel.sendGroup(RType::message::addComponent(_id, "Velocity", new Haze::VelocityData{VELOCITY_WALL_X, VELOCITY_WALL_Y, VELOCITY_WALL_TIME}, sizeof(Haze::VelocityData)));
    auto scale_y = (float) ((_isGround ? -1.0 : 1.0) * UNIVERSAL_SCALE);
    _dataGame.channel.sendGroup(RType::message::addComponent(_id, "Scale", new Haze::ScaleData{UNIVERSAL_SCALE, scale_y}, sizeof(Haze::ScaleData)));
    _dataGame.channel.sendGroup(RType::message::addComponent(_id, "Hitbox", new Haze::HitboxData{{0, 0, frame.width, frame.height}}, sizeof(Haze::HitboxData)));
    _dataGame.channel.sendGroup(RType::message::addComponent(_id, "SpriteCropped", new Haze::SpriteCroppedData{_frameIndex}, sizeof(Haze::SpriteCroppedData)));

    auto elem_sprite = new Haze::SpriteData();
    std::string path_sprite = "";
    try {
        path_sprite = _dataJSON["path_sprite"];
    } catch (std::exception &e) {
        std::cerr << "Error parsing JSON file: " << _dataJSON << std::endl;
        std::cerr << e.what() << std::endl;
    }
    strncpy(elem_sprite->path, path_sprite.c_str(), sizeof(elem_sprite->path));
    elem_sprite->path[sizeof(elem_sprite->path) - 1] = '\0';
    _dataGame.channel.sendGroup(RType::message::addComponent(_entity->getId(), "Sprite", elem_sprite, sizeof(Haze::SpriteData)));

    auto elem_animation = new Haze::AnimationData();
    strncpy(elem_animation->path, _wall_json_path.c_str(), sizeof(elem_animation->path));
    elem_animation->path[sizeof(elem_animation->path) - 1] = '\0';
    _dataGame.channel.sendGroup(RType::message::addComponent(_entity->getId(), "Animation", elem_animation, sizeof(Haze::AnimationData)));
    //    _dataGame.channel.sendGroup(RType::message::addComponent(_id, "HitboxDisplay", nullptr, 0));
}

void Wall::stopVelocity()
{
    // TODO : made the same for enemies
    _entity->addComponent(new Haze::Velocity(0, VELOCITY_WALL_Y, VELOCITY_WALL_TIME));

    float pos = get_x_position();
    _dataGame.channel.sendGroup(RType::message::addComponent(_id, "Velocity", new Haze::VelocityData{0, VELOCITY_WALL_Y, VELOCITY_WALL_TIME}, sizeof(Haze::VelocityData)));
    _dataGame.channel.sendGroup(RType::message::addComponent(_id, "Position", new Haze::PositionData{pos, _y}, sizeof(Haze::PositionData)));
}

void Wall::destroy()
{
    // Send a message to initiate the destruction of the wall entity
    _dataGame.channel.sendGroup(RType::message::deleteEntity(_entity->getId()));

    // Add a Destroy component to the entity
    _entity->addComponent(new Haze::Destroy());

    // Set the entity to nullptr
    _entity = nullptr;
}

float Wall::get_x_position() const
{
    auto wallPos = dynamic_cast<Haze::Position *>(_entity->getComponent("Position"));
    if (wallPos == nullptr) {
        return -1.0;
    }
    return wallPos->x;
}