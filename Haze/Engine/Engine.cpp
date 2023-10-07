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

namespace Haze
{
    Engine::Engine()
    {
    }

    Engine::~Engine()
    {
    }

    void Engine::init()
    {
        _componentList = new ComponentList();
        _pipelines.push_back(std::make_unique<CorePipeline>(this));
        #ifdef USE_SFML
        _pipelines.push_back(std::make_unique<GfxPipeline>(this));
        #endif
    }

    void Engine::update()
    {
        for (int i = 0; i < _pipelines.size(); i++)
            _pipelines[i]->runSystem(_componentList);
        _tics++;
    }

    bool Engine::isOpen()
    {
        for (int i = 0; i < _componentList->getSize(); i++)
        {
            if (_componentList->getComponent("Window", i) != nullptr)
            {
                #ifdef USE_SFML
                auto window = static_cast<Window *>(_componentList->getComponent("Window", i));
                return window->window.isOpen();
                #endif
                return true;
            }
        }
        return false;
    }

    Entity *Engine::createEntity()
    {
        Entity *entity = new Entity();
        entity->setComponentList(_componentList);
        entity->setId(_entities.size());
        _entities.push_back(std::unique_ptr<Entity>(entity));
        _componentList->addEntity();
        return entity;
    }

    Entity *Engine::getEntity(size_t id)
    {
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
}
