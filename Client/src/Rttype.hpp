/*
** EPITECH PROJECT, 2023
** cpp r-type
** File description:
** Rtype.hpp
*/

#pragma once

#include <haze-core.hpp>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include "json.hpp"

class Rttype
{
private:
    Haze::Engine engine;
    Haze::Entity *entityVortex;
    Haze::Entity *entitySpaceship;
    Haze::Entity *entityEnnemy;
    Haze::Entity *entityWindow;
    Haze::Entity *entityWallTop;
    Haze::Entity *entityWallBottom1;
    Haze::Entity *entityWallBottom2;
    Haze::Entity *entityWallBottom3;
    Haze::Entity *entityWallBottom4;
    Haze::Entity *entityWallBottom5;
    Haze::Entity *entityWallBottom6;
    Haze::Sprite *wallSprite = new Haze::Sprite("assets/wall.png");
    nlohmann::json jsonData;
    nlohmann::json sheet;
#ifdef USE_SFML
    sf::Event event;
#endif
    char isMoving = '\0';
    void keyPress();
    void keyRelease();
    void moveSpaceship();
    void moveBackground();
    void changeSpriteBack(Haze::Entity *E);

public:
    Rttype();
    ~Rttype();
    void run();
    void moveUp(void *component);
    void moveDown(void *component);
    void moveLeft(void *component);
    void moveRight(void *component);
};
