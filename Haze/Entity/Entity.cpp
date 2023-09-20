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

    void Entity::AddComponent(Component *component)
    {
        _components.push_back(std::unique_ptr<Component>(component));
    }

    void Entity::RemoveComponent(std::string type)
    {
        for (auto it = _components.begin(); it != _components.end(); it++) {
            if ((*it)->getType() == type) {
                _components.erase(it);
                return;
            }
        }
    }

    Component *Entity::GetComponent(std::string type)
    {
        for (auto it = _components.begin(); it != _components.end(); it++) {
            if ((*it)->getType() == type) {
                return (*it).get();
            }
        }
        return nullptr;
    }

    bool Entity::hasComponent(std::string type)
    {
        for (auto it = _components.begin(); it != _components.end(); it++) {
            if ((*it)->getType() == type) {
                return true;
            }
        }
        return false;
    }

    void Entity::showComponents()
    {
        for (auto it = _components.begin(); it != _components.end(); it++) {
            (*it)->show();
        }
    }
}
