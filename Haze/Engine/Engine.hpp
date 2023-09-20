/*
** EPITECH PROJECT, 2023
** B-CPP-500-MAR-5-1-rtype-erwan.gonzales
** File description:
** Engine
*/

#pragma once
#include <iostream>
#include <vector>
#include "System.hpp"
#include "Entity.hpp"

namespace Haze {
    class Engine {
        public:
            Engine();
            ~Engine();
            void init();
            void update();
            void addEntity(Entity *entity);

        protected:
        private:
            std::vector<std::unique_ptr<Entity>> _entities;

    };
}
