/*
** EPITECH PROJECT, 2023
** B-CPP-500-MAR-5-1-rtype-erwan.gonzales
** File description:
** System
*/

#include "System.hpp"

namespace Haze {
    void MoveSystem(std::vector<std::unique_ptr<Entity>> &entities)
    {
        for (auto &entity : entities) {
            if (entity->hasComponent("Position") && entity->hasComponent("Velocity")) {
                auto position = static_cast<Position *>(entity->GetComponent("Position"));
                auto velocity = static_cast<Velocity *>(entity->GetComponent("Velocity"));
                position->x += velocity->x;
                position->y += velocity->y;
            }
        }
    }

    void RenderSystem(std::vector<std::unique_ptr<Entity>> &entities)
    {
        for (auto &entity : entities) {
            if (entity->hasComponent("Position") && entity->hasComponent("Sprite") && entity->hasComponent("Window")) {
                auto position = static_cast<Position *>(entity->GetComponent("Position"));
                auto sprite = static_cast<Sprite *>(entity->GetComponent("Sprite"));
                auto window = static_cast<Window *>(entity->GetComponent("Window"));
                sprite->sprite.setPosition(position->x, position->y);
                window->window.draw(sprite->sprite);
            }
        }
    }

    void DisplaySystem(std::vector<std::unique_ptr<Entity>> &entities)
    {
        for (auto &entity : entities) {
            if (entity->hasComponent("Window")) {
                auto window = static_cast<Window *>(entity->GetComponent("Window"));
                window->window.display();
            }
        }
    }

    void ClearSystem(std::vector<std::unique_ptr<Entity>> &entities)
    {
        for (auto &entity : entities) {
            if (entity->hasComponent("Window")) {
                auto window = static_cast<Window *>(entity->GetComponent("Window"));
                window->window.clear();
            }
        }
    }
}