/*
** EPITECH PROJECT, 2023
** B-CPP-500-MAR-5-1-rtype-erwan.gonzales
** File description:
** System
*/

#pragma once
#include "Entity.hpp"
#include <vector>

namespace Haze {
    void MoveSystem(std::vector<std::unique_ptr<Entity>> &entities);
}