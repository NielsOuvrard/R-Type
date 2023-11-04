/*
** EPITECH PROJECT, 2023
** B-CPP-500-MAR-5-1-rtype-erwan.gonzales
** File description:
** hazeGfx
*/

#pragma once
#include "IPipeline.hpp"
#include "SystemCore.hpp"
#include "Engine.hpp"

namespace Haze
{
    class CorePipeline : public APipeline {
        public:
            CorePipeline(Engine *engine);
            ~CorePipeline();
            ComponentList *getComponentList() { return _engine->getComponentList(); }
            std::vector<info_inputs> *getInputs() { return _engine->getInfoInputs(); }

        protected:
        private:
            Engine *_engine;
    };
}