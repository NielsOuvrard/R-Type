/*
** EPITECH PROJECT, 2023
** B-CPP-500-MAR-5-1-rtype-erwan.gonzales
** File description:
** Engine
*/

#include "Engine.hpp"

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
        _componentList->addList("Position");
        _componentList->addList("Velocity");
        _componentList->addList("Sprite");
        _componentList->addList("Window");
        _componentList->addList("VelocityOnClick");
        _componentList->addList("Animation");
    }

    void Engine::update()
    {
        MoveSystem(_componentList);
        ClearSystem(_componentList);
        AnimationSystem(_componentList);
        RenderSystem(_componentList);
        EventSystem(_componentList);
        DisplaySystem(_componentList);
        VelocityOnClickSystem(_componentList, "d");
    }

    bool Engine::isOpen()
    {
        for (int i = 0; i < _componentList->getSize(); i++)
        {
            if (_componentList->getComponent("Window", i) != nullptr)
            {
                auto window = static_cast<Window *>(_componentList->getComponent("Window", i));
                return window->window.isOpen();
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
        _componentList->addRow();
        for (auto &it : _componentList->getComponentName())
        {
            if (entity->getComponent(it) != nullptr)
                _componentList->addComponent(entity->getComponent(it), entity->getId());
        }
        return entity;
    }

    void Engine::removeEntity(size_t id)
    {
        _entities[id] = nullptr;
        _componentList->removeRow(id);
    }

    void Engine::removeEntity(Entity *entity)
    {
        _entities[entity->getId()] = nullptr;
        _componentList->removeRow(entity->getId());
    }
}