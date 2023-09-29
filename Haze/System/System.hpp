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
    void ScaleSystem(ComponentList *componentList);
    void MoveSystem(ComponentList *componentList);
    void AnimationSystem(ComponentList *componentList);
    void RenderSystem(ComponentList *componentList);
    void CollisionSystem(ComponentList *componentList);
    void DisplaySystem(ComponentList *componentList);
    void ClearSystem(ComponentList *componentList);
    void VelocityOnClickSystem(ComponentList *componentList, std::string input);
    void EventSystem(ComponentList *componentList);
    void SplitSpriteSystem(ComponentList *componentList);
    void DestroyEntity (ComponentList *componentList, int tics);
}