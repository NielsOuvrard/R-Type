/*
** EPITECH PROJECT, 2023
** B-CPP-500-MAR-5-1-rtype-erwan.gonzales
** File description:
** Entity
*/

#include "Entity.hpp"

namespace Haze {
    Entity::Entity()
    {
    }

    Entity::~Entity()
    {
    }

    void Entity::addComponent(Component *component)
    {
        _components.push_back(component);
        if (_componentList != nullptr) {
            _componentList->addComponent(component, _id);
        }
    }

    void Entity::removeComponent(std::string type)
    {
        for (auto *component : _components) {
            if (component->getType() == type) {
                delete component;
                _components.erase(std::remove(_components.begin(), _components.end(), component), _components.end());
                _componentList->removeComponent(type, _id);
                break;
            }
        }
    }

    Component *Entity::getComponent(std::string type)
    {
        for (auto *component : _components) {
            if (component->getType() == type) {
                return component;
            }
        }
        return nullptr;
    }

    void Entity::showComponents()
    {
        for (auto *component : _components) {
            std::cout << component->getType() << std::endl;
        }
    }

    void Entity::setComponentList(ComponentList *componentList)
    {
        _componentList = componentList;
    }

    void Entity::setId(size_t id)
    {
        _id = id;
    }

    void Entity::setUniqueId(size_t id)
    {
        uniqueId = id;
    }
}
