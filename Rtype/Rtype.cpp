/*
** EPITECH PROJECT, 2023
** cpp r-type
** File description:
** R-Type.cpp
*/

#include "Rtype.hpp"

int Rtype::run()
{
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
    player->showComponents();
    return 0;
}


Rtype::Rtype()
{
    engine.init();
    player = engine.createEntity();
    window = engine.createEntity();
    player->addComponent(new Haze::Position(0, 0));
    player->addComponent(new Haze::Sprite("assets/ship.png"));
    std::vector<std::vector<std::string>> params = {{"z", "0","1"}, {"s", "0","-1"}, {"d", "1","0"}, {"q", "-1","0"}};
    player->addComponent(new Haze::VelocityOnClick(params));

    window->addComponent(new Haze::Window(800, 600));
    // std::chrono::time_point<std::chrono::high_resolution_clock> currentTime, lastTime;
    // double lag = 0.0;

    
}

Rtype::~Rtype()
{
}
