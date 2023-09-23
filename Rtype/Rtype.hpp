/*
** EPITECH PROJECT, 2023
** cpp r-type
** File description:
** R-type.hpp
*/

#pragma once

#include <iostream>
#include <haze.hpp>
#include <chrono>
#include "Engine.hpp"
#include <thread>

class Rtype
{
private:
    const double desiredFPS = 10.0;
    const double frameDuration = 1.0 / desiredFPS;
    Haze::Engine engine;
    Haze::Entity *player;
    Haze::Entity *window;

public:
    Rtype();
    ~Rtype();
    int run();
};

