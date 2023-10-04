/*
** EPITECH PROJECT, 2023
** B-CPP-500-MAR-5-1-rtype-erwan.gonzales
** File description:
** Component
*/

#pragma once
#include <iostream>
#include <string>
#include <chrono>
#include <vector>
#include <memory>
#include <functional>
#include <unordered_map>
#include <map>

namespace Haze
{
    class Component
    {
    public:
        virtual ~Component() {}
        virtual std::string getType() const = 0;
        virtual void show() const = 0;
    };

    struct Position : public Component
    {
        Position(float x, float y) : x(x), y(y) {}
        float x;
        float y;
        float oldX = x;
        float oldY = y;
        std::string getType() const override { return "Position"; }
        void show() const override { std::cout << "Position: " << x << ", " << y << std::endl; }
    };

    struct Scale : public Component
    {
        Scale(float x, float y) : x(x), y(y) {}
        float x;
        float y;
        std::string getType() const override { return "Scale"; }
        void show() const override { std::cout << "Scale: " << x << ", " << y << std::endl; }
    };

    struct Velocity : public Component
    {
        Velocity(float x, float y) : x(x), y(y) {}
        float x;
        float y;
        std::string getType() const override { return "Velocity"; }
        void show() const override { std::cout << "Velocity: " << x << ", " << y << std::endl; }
    };

    struct VelocityOnClick : public Component // useless ?
    {
        // std::vector<std::vector<std::string>> [0] = touche, [1] = velocity x, [2] velocity y
        VelocityOnClick(std::vector<std::vector<std::string>> directions) : diretionTop(directions[0]), diretionBot(directions[1]),
                                                                            diretionRight(directions[2]), diretionLeft(directions[3]) {}
        std::vector<std::string> diretionTop;
        std::vector<std::string> diretionBot;
        std::vector<std::string> diretionRight;
        std::vector<std::string> diretionLeft;
        std::string getType() const override { return "VelocityOnClick"; }
        void show() const override { std::cout << "VelocityOnClick: flm de tout marquer mdr" << std::endl; }
    };

    struct Health : public Component
    {
        Health(int health) : health(health) {}
        int health;
        std::string getType() const override { return "Health"; }
        void show() const override { std::cout << "Health: " << health << std::endl; }
    };

    struct Damage : public Component
    {
        Damage(int damage) : damage(damage) {}
        int damage;
        std::string getType() const override { return "Damage"; }
        void show() const override { std::cout << "Damage: " << damage << std::endl; }
    };

    // will be use in move system
    struct Speed : public Component
    {
        Speed(int speed) : speed(speed) {}
        int speed;
        std::string getType() const override { return "Speed"; }
        void show() const override { std::cout << "Speed: " << speed << std::endl; }
    };

    struct Inputs : public Component // useless ?
    {
        Inputs(int inputs) : inputs(inputs) {}
        int inputs;
        std::string getType() const override { return "Inputs"; }
        void show() const override { std::cout << "Inputs: " << inputs << std::endl; }
    };

    struct Collision : public Component
    {
        enum CollisionType
        {
            NONE = 0,
            LAMBDA = 1,
            WALL = 2,
        };
        struct CollisionInfo
        {
            CollisionType type;
            double tics;

            std::function<void(int, int)> onCollision = [](int i, int j) {};
            std::chrono::time_point<std::chrono::high_resolution_clock> lastCollision = std::chrono::high_resolution_clock::now();
        };
        Collision(std::string scene, std::map<std::string, CollisionInfo> behavior)
            : scene(scene), behavior(behavior) {}

        std::string scene;
        std::map<std::string, CollisionInfo> behavior;

        std::string getType() const override { return "Collision"; }
        void show() const override { std::cout << "Collision: " << scene << std::endl; }
    };

    struct Hitbox : public Component
    {
        struct floatRect
        {
            int x;
            int y;
            int width;
            int height;
        };
        Hitbox(std::vector<floatRect> hitbox) : hitbox(hitbox) {}
        std::vector<floatRect> hitbox;
        std::string getType() const override { return "Hitbox"; }
        void show() const override { std::cout << "Hitbox: " << std::endl; }
    };

    struct LifeTime : public Component
    {
        LifeTime(int lifeTime) : lifeTime(lifeTime) {}
        int lifeTime;
        int tics = 0;
        std::string getType() const override { return "LifeTime"; }
        void show() const override { std::cout << "LifeTime: " << lifeTime << std::endl; }
    };
}
