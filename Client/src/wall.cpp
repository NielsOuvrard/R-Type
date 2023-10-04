/*
** EPITECH PROJECT, 2023
** cpp r-type
** File description:
** wall.cpp
*/

#include "wall.hpp"
#include <haze-graphics.hpp>

wall::wall(Haze::Engine *engine, nlohmann::json data, int x, int y) : _jsonData(data)
{
    _entityWallBottom = engine->createEntity();
    _sheet = _jsonData["sheet1"];
    Haze::Sprite *wallSprite = new Haze::Sprite("assets/wall.png");
    _entityWallBottom->addComponent(new Haze::Position(x, y));
    _entityWallBottom->addComponent(new Haze::Scale(4, -4));
    _entityWallBottom->addComponent(wallSprite);
    _entityWallBottom->addComponent(new Haze::HitboxDisplay());
    _entityWallBottom->addComponent(new Haze::SplitSprite(*static_cast<Haze::Sprite *>(_entityWallBottom->getComponent("Sprite")),
         _sheet["x"], _sheet["y"], _sheet["width"], _sheet["height"]));
    Haze::Collision::CollisionInfo colisionInfo;
    colisionInfo.type = Haze::Collision::LAMBDA;
    colisionInfo.tics = 1;
    colisionInfo.onCollision = [](int x, int y) {
        std::cout << "collision!" << std::endl;
    };
    std::map<std::string, Haze::Collision::CollisionInfo> infos = {
        {"player", colisionInfo},
    };
    _entityWallBottom->addComponent(new Haze::Collision("wall", infos));
    int height = _sheet["height"];
    int width = _sheet["width"];
    std::cout << "height: " << height << std::endl;
    std::cout << "width: " << width << std::endl;
    _entityWallBottom->addComponent(new Haze::Hitbox({{
        0, 0, width, height
    }}));
    _entityWallBottom->addComponent(new Haze::Velocity(-1, 0));
    changeSpriteBack(_entityWallBottom);
}

wall::~wall()
{
}

void wall::changeSpriteBack(Haze::Entity *E)
{
    int randomNumber = std::rand() % 10 + 1;
    _sheet = _jsonData["sheet" + std::to_string(randomNumber)];
    auto splitSprite = static_cast<Haze::SplitSprite *>(E->getComponent("SplitSprite"));
    splitSprite->x = _sheet["x"];
    splitSprite->y = _sheet["y"];
    splitSprite->width = _sheet["width"];
    splitSprite->height = _sheet["height"];
}