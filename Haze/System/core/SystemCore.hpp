/*
** EPITECH PROJECT, 2023
** B-CPP-500-MAR-5-1-rtype-erwan.gonzales
** File description:
** System
*/

#pragma once
#include "Entity.hpp"
#include "ComponentList.hpp"
#include <vector>

namespace Haze
{
    void MoveSystem(ComponentList *componentList);
    void CollisionSystem(ComponentList *componentList);
    void DestroyEntity (ComponentList *componentList);
}