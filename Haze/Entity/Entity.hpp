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

#include "Component.hpp"

namespace Haze {
    class Entity {
        public:
            Entity();
            ~Entity();
            void AddComponent(Component *component);
            void RemoveComponent(std::string type);
            Component *GetComponent(std::string type);
            bool hasComponent(std::string type);
            void showComponents();

        private:
            std::vector<std::unique_ptr<Component>> _components;
    };
}