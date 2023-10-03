/*
** EPITECH PROJECT, 2023
** B-CPP-500-MAR-5-1-rtype-erwan.gonzales
** File description:
** System
*/

#pragma once
#include "Entity.hpp"
#include "ComponentList.hpp"
#include "ComponentGfx.hpp"
#include <vector>

namespace Haze
{
    void ScaleSystem(ComponentList *componentList);
    void AnimationSystem(ComponentList *componentList);
    void RenderSystem(ComponentList *componentList);
    void DisplaySystem(ComponentList *componentList);
    void ClearSystem(ComponentList *componentList);
    void SplitSpriteSystem(ComponentList *componentList);
}