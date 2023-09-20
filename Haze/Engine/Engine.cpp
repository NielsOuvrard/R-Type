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

    void Engine::init()
    {
        std::cout << "Engine is running" << std::endl;
    }

    void Engine::update()
    {
        MoveSystem(_entities);
    }

    void Engine::addEntity(Entity *entity)
    {
        _entities.push_back(std::unique_ptr<Entity>(entity));
    }
}
