/*
** EPITECH PROJECT, 2023
** cpp r-type
** File description:
** Rtype.hpp
*/

#pragma once

#include <haze.hpp>
#include "GraphicClient.hpp"
#include "Component.hpp"

class Rttype
{
    Haze::Engine engine;
    Haze::Entity *entityVortex = engine.createEntity();
    Haze::Entity *entitySpaceship = engine.createEntity();
    Haze::Entity *entityWindow = engine.createEntity();
    Haze::Entity *entityWall = engine.createEntity();
    char isMoving = '\0';
    Haze::Velocity *velocityPlayer = new Haze::Velocity(0, 0);
    Haze::Sprite *vortexSprite = new Haze::Sprite("assets/r-typesheet30a.gif");
    Haze::Sprite *spaceshipSprite = new Haze::Sprite("assets/r-typesheet1.gif");
    Haze::Sprite *wallSprite = new Haze::Sprite("assets/wall.png");
    Haze::Window *window = new Haze::Window(800, 600);

public:
    Rttype();
    ~Rttype();
    void run();
    void moveUp(void *component);
    void moveDown(void *component);
    void moveLeft(void *component);
    void moveRight(void *component);
};


