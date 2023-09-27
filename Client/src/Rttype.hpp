/*
** EPITECH PROJECT, 2023
** cpp r-type
** File description:
** Rtype.hpp
*/

#pragma once

#include <haze.hpp>
// #include "GraphicClient.hpp"
// #include "Component.hpp"

class Rttype
{
    private:
        Haze::Engine engine;
        Haze::Entity *entityVortex;
        Haze::Entity *entitySpaceship;
        Haze::Entity *entityWindow;
        Haze::Entity *entityWall;
        sf::Event event;
        char isMoving = '\0';
        void keyPress();
        void keyRelease();
        void moveSpaceship();

    public:
        Rttype();
        ~Rttype();
        void run();
        void moveUp(void *component);
        void moveDown(void *component);
        void moveLeft(void *component);
        void moveRight(void *component);
};


