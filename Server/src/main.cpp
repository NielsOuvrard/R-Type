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
    entity1->addComponent(new Haze::Health(100));
    entity1->addComponent(new Haze::Collision(
        "player",
        std::map<std::string, Haze::Collision::CollisionInfo>{
            {"enemy", Haze::Collision::CollisionInfo{
                Haze::Collision::CollisionType::NONE,
                1.0
            }}
        }
    ));

    Haze::Collision::CollisionInfo info;
    info.type = Haze::Collision::CollisionType::LAMBDA;
    info.tics = 1.0;
    info.onCollision = [&engine](int i, int j) {
        Haze::Entity *test = engine.createEntity();
        test->addComponent(new Haze::Position(500, 0));
        test->addComponent(new Haze::Sprite("assets/ship.png"));
        test->addComponent(new Haze::Velocity(-1, 0));
        test->addComponent(new Haze::Scale(0.5, 0.5));
        test->addComponent(new Haze::Size(400, 400));
    };

    entity3->addComponent(new Haze::Position(500, 0));
    entity3->addComponent(new Haze::Sprite("assets/ship.png"));
    entity3->addComponent(new Haze::Velocity(-1, 0));
    entity3->addComponent(new Haze::Scale(0.5, 0.5));
    entity3->addComponent(new Haze::Size(400, 400));
    entity3->addComponent(new Haze::Collision(
        "enemy",
        std::map<std::string, Haze::Collision::CollisionInfo>{
            {"player", info}
        }
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
