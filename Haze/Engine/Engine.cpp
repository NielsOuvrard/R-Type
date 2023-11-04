/*
** EPITECH PROJECT, 2023
** B-CPP-500-MAR-5-1-rtype-erwan.gonzales
** File description:
** Engine
*/

#include "Engine.hpp"

#include "CorePipeline.hpp"
#ifdef USE_SFML
#include "GfxPipeline.hpp"
#endif
#include <iostream>
#include <unistd.h>

namespace Haze {
    Engine::Engine(int framerate, int lib)
    {
        _framerate = framerate;
#ifdef USE_SFML
        setGfxLib(lib);
#endif
    }

    Engine::~Engine()
    {
    }

    void Engine::init()
    {
        _componentList = new ComponentList();
#ifdef USE_SFML
        _pipelines.push_back(std::make_unique<GfxPipeline>(this));
#endif
        _pipelines.push_back(std::make_unique<CorePipeline>(this));
        std::cout << "Engine init" << std::endl;
    }

    void Engine::update()
    {
        std::chrono::time_point<std::chrono::system_clock> now = std::chrono::system_clock::now();
        std::chrono::duration<double> elapsed_seconds = now - _lastTime;
        if (elapsed_seconds.count() < 1.0 / _framerate)
            return;
        _lastTime = now;
        for (int i = 0; i < _pipelines.size(); i++)
            _pipelines[i]->runSystem(_componentList);
    }

    bool Engine::isOpen()
    {
        for (int i = 0; i < _componentList->getSize(); i++) {
            if (_componentList->getComponent("Window", i) != nullptr) {
#ifdef USE_SFML
                auto window = static_cast<Window *>(_componentList->getComponent("Window", i));
                if (window == nullptr)
                    return true;
                return window->window->isOpen();
#endif
                return true;
            }
        }
        return true;
    }

    Entity *Engine::createEntity()
    {
        Entity *entity = new Entity(_componentList, _entities.size());
        _entities.push_back(std::unique_ptr<Entity>(entity));
        _componentList->addEntity();
        return entity;
    }

    Entity *Engine::getEntity(size_t id)
    {
        if (id >= _entities.size())
            return nullptr;
        return _entities[id].get();
    }

    void Engine::removeEntity(size_t id)
    {
        _entities[id] = nullptr;
        _componentList->removeEntity(id);
    }

    void Engine::removeEntity(Entity *entity)
    {
        _entities[entity->getId()] = nullptr;
        _componentList->removeEntity(entity->getId());
    }

    void Engine::setInfoInputs(info_inputs info, size_t id)
    {
        if (id == _infoInputs.size())
            _infoInputs.push_back(info);
        else
            _infoInputs[id] = info;
    }
}// namespace Haze
