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
#include "matrix.hpp"

namespace Haze
{
    void SizeSystem(ComponentList *componentList);
    void ScaleSystem(ComponentList *componentList);
    void MoveSystem(ComponentList *componentList);
    void AccelerationSystem(ComponentList *componentList);
    void AnimationSystem(ComponentList *componentList);
    void RenderSystem(ComponentList *componentList);
    void CollisionSystem(ComponentList *componentList);
    void DisplaySystem(ComponentList *componentList);
    void ClearSystem(ComponentList *componentList);
    void VelocityOnClickSystem(ComponentList *componentList, std::string input);
    void EventSystem(ComponentList *componentList);
}