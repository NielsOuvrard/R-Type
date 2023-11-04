/*
** EPITECH PROJECT, 2023
** B-CPP-500-MAR-5-1-rtype-erwan.gonzales
** File description:
** System
*/

#pragma once
#include "Entity.hpp"
#include "ComponentList.hpp"
#include "protocol.hpp"
#include <chrono>
#include <vector>
#include <math.h>

namespace Haze
{
    void useInputs(ComponentList *componentList, std::vector<info_inputs> *inputs);
    void MoveSystem(ComponentList *componentList, std::vector<info_inputs> *inputs);
    void CollisionSystem(ComponentList *componentList, std::vector<info_inputs> *inputs);
    void DestroyEntity (ComponentList *componentList, std::vector<info_inputs> *inputs);
}