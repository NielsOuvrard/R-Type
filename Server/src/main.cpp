/*
** EPITECH PROJECT, 2023
** B-CPP-500-MAR-5-1-rtype-erwan.gonzales
** File description:
** main
*/

#include <iostream>
#include <haze.hpp>
#include <chrono>
#include "Engine.hpp"
#include <thread>

const double desiredFPS = 10.0;
const double frameDuration = 1.0 / desiredFPS;

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


    std::chrono::time_point<std::chrono::high_resolution_clock> currentTime, lastTime;
    double lag = 0.0;
    while (1) {
        auto startTime = std::chrono::high_resolution_clock::now();
        engine.update();
        auto endTime = std::chrono::high_resolution_clock::now();
        auto deltaTime = std::chrono::duration<double>(endTime - startTime).count();

        if (deltaTime < frameDuration) {
            double sleepTime = frameDuration - deltaTime;
            std::this_thread::sleep_for(std::chrono::duration<double>(sleepTime));
        }
    }
    entity->showComponents();
    return 0;
}
