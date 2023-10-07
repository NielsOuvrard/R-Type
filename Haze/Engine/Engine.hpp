/*
** EPITECH PROJECT, 2023
** B-CPP-500-MAR-5-1-rtype-erwan.gonzales
** File description:
** Engine
*/

#pragma once
#include <iostream>
#include <vector>
#include <map>
#include "Entity.hpp"
#include "ComponentList.hpp"
#include "IPipeline.hpp"
#include "inputs.hpp"
#include "protocol.hpp"

namespace Haze
{
    class Engine
    {
    public:
        Engine();
        ~Engine();
        void init();
        void update();
        Entity *createEntity();
        Entity *getEntity(size_t id);
        void removeEntity(size_t id);
        void removeEntity(Entity *entity);
        bool isOpen();
        ComponentList *getComponentList() { return _componentList; }
        info_inputs *getInfoInputs() { return &_info_inputs; }

    protected:
    private:
        std::vector<std::unique_ptr<Entity>> _entities;
        std::vector<std::unique_ptr<IPipeline>> _pipelines;
        ComponentList *_componentList;
        info_inputs _info_inputs;

        int _tics = 0;
    };
}
