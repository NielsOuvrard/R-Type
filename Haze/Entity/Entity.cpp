/*
** EPITECH PROJECT, 2023
** B-CPP-500-MAR-5-1-rtype-erwan.gonzales
** File description:
** Entity
*/

#include "Entity.hpp"

namespace Haze {
    Entity::Entity(ComponentList *componentList, size_t id) : _componentList(componentList), _id(id)
    {
    }

    Entity::~Entity()
    {
    }

    void Entity::addComponent(Component *component)
    {
        if (component == nullptr) {
            return;
        }
        _componentList->addComponent(component, _id);
    }

    void Entity::removeComponent(std::string type)
    {
        _componentList->removeComponent(type, _id);
    }

    Component *Entity::getComponent(std::string type)
    {
        return _componentList->getComponent(type, _id);
    }
}// namespace Haze
