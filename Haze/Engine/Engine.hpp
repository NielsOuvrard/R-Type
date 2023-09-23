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
#include "System.hpp"
#include "Entity.hpp"
#include "ComponentList.hpp"

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

    protected:
    private:
        std::vector<std::unique_ptr<Entity>> _entities;
        ComponentList *_componentList;
    };
}
