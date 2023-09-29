/*
** EPITECH PROJECT, 2023
** cpp r-type
** File description:
** Rtype.hpp
*/

#pragma once

#include <haze.hpp>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include "json.hpp"
#include "wall.hpp"

// #include "GraphicClient.hpp"
// #include "Component.hpp"


class Rttype
{
    private:
        Haze::Engine engine;
        Haze::Entity *entityVortex;
        Haze::Entity *entitySpaceship;
        Haze::Entity *entityWindow;
        Haze::Entity *entityWallTop;
        wall *wall1;
        wall *wall2;
        wall *wall3;
        wall *wall4;
        wall *wall5;
        wall *wall6;
        // Haze::Entity *entityBackground;
        Haze::Sprite *wallSprite = new Haze::Sprite("assets/wall.png");
        nlohmann::json jsonData;
        nlohmann::json sheet;
        sf::Event event;
        char isMoving = '\0';
        void keyPress();
        void keyRelease();
        void moveSpaceship();
        void moveBackground();

    public:
        Rttype();
        ~Rttype();
        void run();
        void moveUp(void *component);
        void moveDown(void *component);
        void moveLeft(void *component);
        void moveRight(void *component);
};
