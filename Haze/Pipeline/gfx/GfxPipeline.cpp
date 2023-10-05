/*
** EPITECH PROJECT, 2023
** B-CPP-500-MAR-5-1-rtype-erwan.gonzales
** File description:
** GfxPipeline
*/

#include "GfxPipeline.hpp"

namespace Haze {
    GfxPipeline::GfxPipeline()
    {
        _systems.push_back(ScaleSystem);
        _systems.push_back(AnimateSystem);
        _systems.push_back(PullEvent);
        _systems.push_back(RenderSystem);
        _systems.push_back(DisplaySystem);
        _systems.push_back(ClearSystem);
    }

    GfxPipeline::~GfxPipeline()
    {
    }
}