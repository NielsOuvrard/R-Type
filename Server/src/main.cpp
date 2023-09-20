/*
** EPITECH PROJECT, 2023
** B-CPP-500-MAR-5-1-rtype-erwan.gonzales
** File description:
** main
*/

#include <iostream>
#include <haze.hpp>
#include "Engine.hpp"

int main()
{
    std::cout << "Calling the engine!" << std::endl;
    Haze::Engine engine;
    engine.init();
    Haze::Entity *entity = new Haze::Entity();
    entity->AddComponent(new Haze::Position(0, 0));
    entity->AddComponent(new Haze::Velocity(1, 1));
    entity->AddComponent(new Haze::Window(800, 600));
    entity->AddComponent(new Haze::Sprite("assets/ship.png"));
    engine.addEntity(entity);
    while (1) {
        engine.update();
    }
    entity->showComponents();
    return 0;
}
