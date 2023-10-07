/*
** EPITECH PROJECT, 2023
** B-CPP-500-MAR-5-1-rtype-erwan.gonzales
** File description:
** Entity
*/

#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "ComponentList.hpp"

namespace Haze
{
    class Entity
    {
    public:
        Entity(ComponentList *componentList, size_t _id);
        ~Entity();
        void addComponent(Component *component);
        void removeComponent(std::string type);
        Component *getComponent(std::string type);
        size_t getId() const { return _id; };

    private:
        size_t _id;
        ComponentList *_componentList;
    };
}