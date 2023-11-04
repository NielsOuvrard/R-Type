/*
** EPITECH PROJECT, 2023
** B-CPP-500-MAR-5-1-rtype-erwan.gonzales
** File description:
** CorePipeline
*/

#include "CorePipeline.hpp"

namespace Haze {
    CorePipeline::CorePipeline(Engine *engine) : _engine(engine)
    {
        _systems.push_back(useInputs);
        _systems.push_back(MoveSystem);
        _systems.push_back(CollisionSystem);
        _systems.push_back(DestroyEntity);
    }

    CorePipeline::~CorePipeline()
    {
    }
}