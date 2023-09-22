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
        Entity();
        ~Entity();
        void setComponentList(ComponentList *componentList);
        void setId(size_t id);
        void setUniqueId(size_t id);
        void addComponent(Component *component);
        void removeComponent(std::string type);
        Component *getComponent(std::string type);
        void showComponents();
        size_t getId() const { return _id; };

    private:
        std::vector<Component *> _components;
        size_t _id;
        size_t uniqueId;

        ComponentList *_componentList;
    };
}