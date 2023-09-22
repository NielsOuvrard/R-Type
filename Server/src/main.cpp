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

const double desiredFPS = 60.0;
const double frameDuration = 1.0 / desiredFPS;

int main()
{
    std::cout << "Calling the engine!" << std::endl;
    Haze::Engine engine;
    engine.init();
    Haze::Entity *entity1 = engine.createEntity();
    Haze::Entity *entity2 = engine.createEntity();
    Haze::Entity *entity3 = engine.createEntity();
    entity1->addComponent(new Haze::Position(0, 0));
    entity1->addComponent(new Haze::Sprite("assets/ship.png"));
    entity1->addComponent(new Haze::Velocity(1, 0));
    entity1->addComponent(new Haze::Scale(0.5, 0.5));
    entity1->addComponent(new Haze::Size(400, 400));
    //    Collision(std::string scene, std::map<std::string, CollisionType> behavior) : scene(scene), behavior(behavior) {}
    entity1->addComponent(new Haze::Collision(
        "player",
        std::map<std::string, Haze::Collision::CollisionType>{
            {"player", Haze::Collision::CollisionType::NONE},
            {"enemy", Haze::Collision::CollisionType::WALL},
            {"bullet", Haze::Collision::CollisionType::DAMAGE},
            {"default", Haze::Collision::CollisionType::NONE},
        },
        1
    ));

    entity3->addComponent(new Haze::Position(500, 0));
    entity3->addComponent(new Haze::Sprite("assets/ship.png"));
    entity3->addComponent(new Haze::Velocity(-1, 0));
    entity3->addComponent(new Haze::Scale(0.5, 0.5));
    entity3->addComponent(new Haze::Size(400, 400));
    entity3->addComponent(new Haze::Collision(
        "enemy",
        std::map<std::string, Haze::Collision::CollisionType>{
            {"player", Haze::Collision::CollisionType::NONE},
            {"enemy", Haze::Collision::CollisionType::NONE},
            {"bullet", Haze::Collision::CollisionType::NONE},
            {"default", Haze::Collision::CollisionType::DESTROY},
        },
        1
    ));

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
