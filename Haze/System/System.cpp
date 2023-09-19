/*
** EPITECH PROJECT, 2023
** B-CPP-500-MAR-5-1-rtype-erwan.gonzales
** File description:
** System
*/

#include "System.hpp"

namespace Haze {
    void MoveSystem(std::vector<Entity> &entities)
    {
        for (auto &entity : entities) {
            if (entity.hasComponent("Position") && entity.hasComponent("Velocity")) {
                auto *position = dynamic_cast<Position *>(entity.GetComponent("Position"));
                auto *velocity = dynamic_cast<Velocity *>(entity.GetComponent("Velocity"));
                position->x += velocity->x;
                position->y += velocity->y;
            }
        }
    }
}