/*
** EPITECH PROJECT, 2023
** B-CPP-500-MAR-5-1-rtype-erwan.gonzales
** File description:
** ComponentList
*/

#include "ComponentList.hpp"

namespace Haze {
    ComponentList::ComponentList()
    {
    }

    ComponentList::~ComponentList()
    {
    }

    void ComponentList::addComponent(Component *component, size_t id)
    {
        //        if (_componentName.empty()) {
        //            return;
        //        }
        if (find(_componentName.begin(), _componentName.end(), component->getType()) == _componentName.end()) {
            addList(component->getType());
        }
        _componentList[component->getType()][id] = std::unique_ptr<Component>(component);
    }

    void ComponentList::removeComponent(std::string type, size_t id)
    {
        _componentList[type][id] = nullptr;
    }

    Component *ComponentList::getComponent(std::string type, size_t id)
    {
        if (find(_componentName.begin(), _componentName.end(), type) == _componentName.end()) {
            addList(type);
            return nullptr;
        }
        return _componentList[type][id].get();
    }

    void ComponentList::addList(std::string type)
    {
        _componentName.push_back(type);
        _componentList[type] = std::vector<std::unique_ptr<Component>>(_size);
    }

    void ComponentList::addEntity()
    {
        for (auto &it: _componentList) {
            it.second.push_back(nullptr);
        }
        _size++;
    }

    void ComponentList::removeEntity(size_t id)
    {
        for (auto &it: _componentList) {
            it.second[id] = nullptr;
        }
    }

    void ComponentList::showComponents()
    {
        for (auto &it: _componentList) {
            std::cout << it.first << "   \t";
            for (auto &it2: it.second) {
                if (it2 != nullptr)
                    std::cout << "\tvalue";
                else {
                    std::cout << "\tnull";
                }
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
    }
}// namespace Haze
