/*
** EPITECH PROJECT, 2023
** B-CPP-500-MAR-5-1-rtype-erwan.gonzales
** File description:
** IPipeline
*/

#pragma once
#include <vector>
#include <functional>
#include "ComponentList.hpp"
#include "protocol.hpp"

namespace Haze
{
    class IPipeline {
        public:
            virtual ~IPipeline() = default;
            virtual void runSystem(ComponentList *components) = 0;
            virtual ComponentList *getComponentList() = 0;
            virtual info_inputs *getInputs() = 0;

        protected:
        private:
    };

    class APipeline : public IPipeline {
        public:
            void runSystem(ComponentList *components)
            {
                for (auto &system : _systems)
                    system(getComponentList(), getInputs());
            }

        protected:
            std::vector<std::function<void(ComponentList *, info_inputs *)>> _systems;
        private:
    };
}