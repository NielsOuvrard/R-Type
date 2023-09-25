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

    void Entity::showComponents()
    {
        // for (auto *component : _components) {
        //     std::cout << component->getType() << std::endl;
        // }
    }

    void Entity::setComponentList(ComponentList *componentList)
    {
        _componentList = componentList;
    }

    void Entity::setId(size_t id)
    {
        _id = id;
    }

}
