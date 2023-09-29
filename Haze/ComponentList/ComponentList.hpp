/*
** EPITECH PROJECT, 2023
** B-CPP-500-MAR-5-1-rtype-erwan.gonzales
** File description:
** ComponentList
*/

#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include "Component.hpp"

namespace Haze
{
    class ComponentList
    {
    public:
        ComponentList();
        ~ComponentList();

        void addComponent(Component *component, size_t id);
        void removeComponent(std::string type, size_t id);
        Component *getComponent(std::string type, size_t id);
        void addList(std::string type);
        size_t getSize() const { return _size; };
        void addEntity();
        void removeEntity(size_t id);
        void showComponents();
        std::vector<std::string> getComponentName() const { return _componentName; };

    private:
        std::map<std::string, std::vector<std::unique_ptr<Component>>> _componentList;
        std::vector<std::string> _componentName;
        size_t _size = 0;
    };
}
