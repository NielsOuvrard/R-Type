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
#include "inputs.hpp"

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

    struct Move : public Component
    {
        Move(float x, float y) : x(x), y(y) {}
        float x;
        float y;
        std::string getType() const override { return "Move"; }
        void show() const override { std::cout << "Move: " << x << ", " << y << std::endl; }
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
        struct intRect
        {
            int x;
            int y;
            int width;
            int height;
        };
        Hitbox(std::vector<intRect> hitbox) : hitbox(hitbox) {}
        std::vector<intRect> hitbox;
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

    struct OnKeyPressed : public Component
    {
        OnKeyPressed(std::function<void(int, std::vector<InputType>)> callback, size_t player = 0) : callback(callback), player(player) {}
        std::function<void(int, std::vector<InputType>)> callback;
        size_t player;
        std::string getType() const override
        {
            return "OnKeyPressed";
        }
        void show() const override { std::cout << "OnKeyPressed" << std::endl; }
    };

    struct OnKeyReleased : public Component
    {
        OnKeyReleased(std::function<void(int, std::vector<InputType>)> callback, size_t player = 0) : callback(callback), player(player) {}
        std::function<void(int, std::vector<InputType>)> callback;
        size_t player;
        std::string getType() const override
        {
            return "OnKeyReleased";
        }
        void show() const override { std::cout << "OnKeyReleased" << std::endl; }
    };

    struct OnMousePressed : public Component
    {
        OnMousePressed(std::function<void(int)> callback, size_t player = 0) : callback(callback), player(player) {}
        std::function<void(int)> callback;
        size_t player;
        std::string getType() const override
        {
            return "OnMousePressed";
        }
        void show() const override { std::cout << "OnMousePressed" << std::endl; }
    };

    struct OnMouseReleased : public Component
    {
        OnMouseReleased(std::function<void(int)> callback, size_t player = 0) : callback(callback), player(player) {}
        std::function<void(int)> callback;
        size_t player;
        std::string getType() const override
        {
            return "OnMouseReleased";
        }
        void show() const override { std::cout << "OnMouseReleased" << std::endl; }
    };

    struct Hide : public Component
    {
        Hide() {}
        std::string getType() const override { return "Hide"; }
        void show() const override { std::cout << "Hide" << std::endl; }
    };
}
