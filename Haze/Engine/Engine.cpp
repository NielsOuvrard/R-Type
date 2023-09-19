/*
** EPITECH PROJECT, 2023
** B-CPP-500-MAR-5-1-rtype-erwan.gonzales
** File description:
** Engine
*/

#include "Engine.hpp"

namespace Haze {
    Engine::Engine()
    {
    }

    Engine::~Engine()
    {
    }

    void Engine::run()
    {
        std::cout << "Engine is running" << std::endl;
    }

    void Engine::update()
    {
        std::cout << "Engine is updating" << std::endl;
    }
}