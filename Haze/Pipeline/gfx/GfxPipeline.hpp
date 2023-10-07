/*
** EPITECH PROJECT, 2023
** B-CPP-500-MAR-5-1-rtype-erwan.gonzales
** File description:
** hazeGfx
*/


#pragma once
#include "IPipeline.hpp"
#include "SystemGfx.hpp"
#include "Engine.hpp"

namespace Haze
{
    class GfxPipeline : public APipeline {
        public:
            GfxPipeline(Engine *engine);
            ~GfxPipeline();
            ComponentList *getComponentList() { return _engine->getComponentList(); }
            info_inputs *getInputs() { return _engine->getInfoInputs(); }

        protected:
        private:
            Engine *_engine;
    };
}
