/*
** EPITECH PROJECT, 2023
** B-CPP-500-MAR-5-1-rtype-erwan.gonzales
** File description:
** hazeGfx
*/

#pragma once
#include "Engine.hpp"
#include "IDisplay.hpp"
#include "IPipeline.hpp"
#include "SystemGfx.hpp"
#include <filesystem>
#include <iostream>
#include <vector>

namespace Haze {
    class GfxPipeline : public APipeline {
    public:
        GfxPipeline(Engine *engine);
        ~GfxPipeline();

        ComponentList *getComponentList() { return _engine->getComponentList(); }

        std::vector<info_inputs> *getInputs() { return _engine->getInfoInputs(); }

    protected:
    private:
        Engine *_engine;
    };
}// namespace Haze
