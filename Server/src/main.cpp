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
    Haze::Entity *entity1 = engine.createEntity();
    Haze::Entity *entity2 = engine.createEntity();
    entity1->addComponent(new Haze::Position(0, 0));
    entity1->addComponent(new Haze::Sprite("assets/ship.png"));
    // entity1->AddComponent(new Haze::Velocity(1, 0));
    entity1->addComponent(new Haze::Sprite("assets/ship.png"));
    std::vector<std::vector<std::string>> params = {{"z", "0","1"}, {"s", "0","-1"}, {"d", "1","0"}, {"q", "-1","0"}};
    entity1->addComponent(new Haze::VelocityOnClick(params));
    // entity1->AddComponent(new Haze::Window(800, 600));

    entity2->addComponent(new Haze::Window(800, 600));
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
    entity1->showComponents();
    return 0;
}
