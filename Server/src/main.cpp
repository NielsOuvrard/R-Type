/*
** EPITECH PROJECT, 2023
** B-CPP-500-MAR-5-1-rtype-erwan.gonzales
** File description:
** main
*/

#include "Rtype.hpp"

int main(void)
{
    std::cout << "\033[1;33m";
    std::cout << "calling the server!" << std::endl;

    Rtype rtype;

    // cout in red color
    std::cout << "\033[1;31m";
    std::cout << "calling the server!" << std::endl;

    rtype.run();
    return 0;
}

// #include <iostream>
// #include <haze-core.hpp>
// #include <chrono>
// #include <thread>
// #include "Engine.hpp"
// #include "Rtype.hpp"

// const double desiredFPS = 10.0;
// const double frameDuration = 1.0 / desiredFPS;

// int main()
// {
//     std::cout << "Calling the engine!" << std::endl;
//     Haze::Engine engine;
//     engine.init();
//     Haze::Entity *entity1 = engine.createEntity();
//     Haze::Entity *entity2 = engine.createEntity();
//     entity1->addComponent(new Haze::Position(0, 0));
//     entity1->addComponent(new Haze::Sprite("assets/ship.png"));
//     // entity1->AddComponent(new Haze::Velocity(1, 0));
//     entity1->addComponent(new Haze::Sprite("assets/ship.png"));
//     std::vector<std::vector<std::string>> params = {{"z", "0","1"}, {"s", "0","-1"}, {"d", "1","0"}, {"q", "-1","0"}};
//     entity1->addComponent(new Haze::VelocityOnClick(params));
//     // entity1->AddComponent(new Haze::Window(800, 600));

//     entity2->addComponent(new Haze::Window(800, 600));
//     std::chrono::time_point<std::chrono::high_resolution_clock> currentTime, lastTime;
//     double lag = 0.0;
//     while (1) {
//         auto startTime = std::chrono::high_resolution_clock::now();
//         engine.update();
//         auto endTime = std::chrono::high_resolution_clock::now();
//         auto deltaTime = std::chrono::duration<double>(endTime - startTime).count();
//         if (deltaTime < frameDuration) {
//             double sleepTime = frameDuration - deltaTime;
//             std::this_thread::sleep_for(std::chrono::duration<double>(sleepTime));
//         }
//     }
//     entity1->showComponents();
//     return 0;
// }

// int main()
// {
//     std::cout << std::time(nullptr) << std::endl;
//     // Rtype rtype;
//     std::cout << "Calling the server!" << std::endl;

//     Haze::Engine engine;
//     engine.init();

// Haze::Entity *entitySpaceship = engine.createEntity();
// Haze::Entity *entityEnnemy = engine.createEntity();
// Haze::Sprite *spaceshipSprite = new Haze::Sprite("assets/r-typesheet1.gif");
// Haze::Sprite *ennemySprite = new Haze::Sprite("assets/r-typesheet5.gif");
// Haze::Entity *entityWindow = engine.createEntity();

// entitySpaceship->addComponent(new Haze::Position(100, 200));
// entitySpaceship->addComponent(new Haze::Scale(3, 3));
// entitySpaceship->addComponent(spaceshipSprite);
// entitySpaceship->addComponent(new Haze::Animation(*spaceshipSprite, 100, 0, 33, 18, 5, 1, true));

// entityEnnemy->addComponent(new Haze::Position(500, 200));
// entityEnnemy->addComponent(new Haze::Velocity(0, 0));
// entityEnnemy->addComponent(new Haze::Scale(3, 3));
// entityEnnemy->addComponent(new Haze::Animation(*ennemySprite, 0, 0, 33, 36, 8, 1, true));
// entityEnnemy->addComponent(ennemySprite);

// std::cout << "Entity spaceship: " << entitySpaceship << std::endl;

//     while (engine.isOpen())
//     {
//         engine.update();
//     }

//     // rtype.run();
//     return 0;
// }