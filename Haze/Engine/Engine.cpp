/*
** EPITECH PROJECT, 2023
** B-CPP-500-MAR-5-1-rtype-erwan.gonzales
** File description:
** Engine
*/

#include "Engine.hpp"

void animateThread(int interval_ms, int duration_sec, Haze::Animation *animation)
{
    auto start_time = std::chrono::high_resolution_clock::now();
    while (true)
    {
        auto current_time = std::chrono::high_resolution_clock::now();
        auto elapsed_time = std::chrono::duration_cast<std::chrono::milliseconds>(current_time - start_time).count();

        if (elapsed_time >= duration_sec * 1000)
        {
            break; // Exit the animation loop after the specified duration
        }

        // Animate the sprite
        if (animation->boomerang)
        {
            if (animation->moveUp)
            {
                animation->currentFrame++;
            }
            else
            {
                animation->currentFrame--;
            }
            if (animation->currentFrame == animation->nbFramesX - 1)
            {
                animation->moveUp = false;
            }
            if (animation->currentFrame == 0)
            {
                animation->moveUp = true;
            }
        }
        else
        {
            if (animation->currentFrame == animation->nbFramesX - 1)
            {
                animation->currentFrame = 0;
            }
            else
            {
                animation->currentFrame++;
            }
        }
        animation->sprite.setTextureRect(sf::IntRect(animation->x + (animation->currentFrame * animation->width), animation->y, animation->width, animation->height));
        std::this_thread::sleep_for(std::chrono::milliseconds(interval_ms));
    }
}

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
        _componentList->addList("Scale");
        _componentList->addList("Hitbox");
        _componentList->addList("Damage");
        _componentList->addList("Health");
        _componentList->addList("Position");
        _componentList->addList("Velocity");
        _componentList->addList("Sprite");
        _componentList->addList("Window");
        _componentList->addList("LifeTime");
        _componentList->addList("VelocityOnClick");
        _componentList->addList("Animation");
        _componentList->addList("SplitSprite");
        _componentList->addList("Collision");
        _componentList->addList("SplitSprite");
    }

    void Engine::update()
    {
        ClearSystem(_componentList);
        ScaleSystem(_componentList);
        MoveSystem(_componentList);
        AnimationSystem(_componentList);
        CollisionSystem(_componentList);
        RenderSystem(_componentList);
        DisplaySystem(_componentList);
        SplitSpriteSystem(_componentList);
        DestroyEntity(_componentList, _tics);
        _tics++;
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
