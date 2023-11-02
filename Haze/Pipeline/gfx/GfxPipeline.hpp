/*
** EPITECH PROJECT, 2023
** B-CPP-500-MAR-5-1-rtype-erwan.gonzales
** File description:
** hazeGfx
*/

#pragma once
#include <iostream>
#include <vector>
#include "IPipeline.hpp"
#include "IDisplay.hpp"
#include "SystemGfx.hpp"
#include "Engine.hpp"
#include <filesystem>

namespace Haze
{
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
}
