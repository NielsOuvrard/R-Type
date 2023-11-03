/*
** EPITECH PROJECT, 2023
** B-CPP-500-MAR-5-1-rtype-erwan.gonzales
** File description:
** Component
*/

#pragma once
#include "inputs.hpp"
#include <chrono>
#include <functional>
#include <iostream>
#include <map>
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

namespace Haze {
    class Component {
    public:
        virtual ~Component() {}

        virtual std::string getType() const = 0;
        virtual void show() const = 0;
    };

    struct PositionInterpolation : public Component {
        PositionInterpolation(float prevX, float prevY, float nextX, float nextY) : prevX(prevX), prevY(prevY), nextX(nextX), nextY(nextY) {}

        float prevX;
        float prevY;
        float nextX;
        float nextY;

        std::string getType() const override { return "PositionInterpolation"; }

        void show() const override { std::cout << "PositionInterpolation: " << prevX << ", " << prevY << ", " << nextX << ", " << nextY << std::endl; }
    };

    struct Interpolation : public Component {
        Interpolation(int framerate) : framerate(framerate) {}

        int framerate;

        std::string getType() const override { return "Interpolation"; }

        void show() const override { std::cout << "Interpolation: " << framerate << std::endl; }
    };

    struct Position : public Component {
        Position(float x, float y) : x(x), y(y) {}

        float x;
        float y;

        std::string getType() const override { return "Position"; }

        void show() const override { std::cout << "Position: " << x << ", " << y << std::endl; }
    };

    struct Scale : public Component {
        Scale(float x, float y) : x(x), y(y) {}

        float x;
        float y;

        std::string getType() const override { return "Scale"; }

        void show() const override { std::cout << "Scale: " << x << ", " << y << std::endl; }
    };

    struct Velocity : public Component {
        Velocity(float x, float y, float time) : x(x), y(y), tick(time) {}

        float x;
        float y;
        float tick;
        std::chrono::time_point<std::chrono::high_resolution_clock> lastUpdate = std::chrono::high_resolution_clock::now();

        std::string getType() const override { return "Velocity"; }

        void show() const override { std::cout << "Velocity: " << x << ", " << y << std::endl; }
    };

    struct VelocityInterpolation : public Component {
        VelocityInterpolation(float x, float y, float time) : x(x), y(y), tick(time) {}

        float x;
        float y;
        float tick;

        std::chrono::time_point<std::chrono::high_resolution_clock> lastUpdate = std::chrono::high_resolution_clock::now();
        std::chrono::time_point<std::chrono::high_resolution_clock> fullUpdate = std::chrono::high_resolution_clock::now();

        std::string getType() const override { return "VelocityInterpolation"; }

        void show() const override { std::cout << "VelocityInterpolation: " << x << ", " << y << std::endl; }
    };

    struct SinVelocity : public Component {
        SinVelocity(float x, float time, float amplitude, float frequency, float offset = 0) : x(x), tick(time), amplitude(amplitude), frequency(frequency), offset(offset) {}

        float x;
        float tick;
        float amplitude;
        float frequency;
        float offset;
        bool applied = false;
        std::chrono::time_point<std::chrono::high_resolution_clock> lastUpdate = std::chrono::high_resolution_clock::now();

        std::string getType() const override { return "SinVelocity"; }

        void show() const override { std::cout << "SinVelocity: " << x << ", " << tick << std::endl; }
    };

    struct CircleVelocity : public Component {
        CircleVelocity(float x, float time, float radius, float offset = 0) : x(x), tick(time), radius(radius), t(offset) {}

        float x;
        float tick;
        float radius;
        float t = 0;
        bool applied = false;
        std::chrono::time_point<std::chrono::high_resolution_clock> lastUpdate = std::chrono::high_resolution_clock::now();

        std::string getType() const override { return "CircleVelocity"; }

        void show() const override { std::cout << "CircleVelocity: " << std::endl; }
    };

    struct BulletDrop : public Component {
        BulletDrop(float strength, float angle, float time) : strength(strength), angle(angle), tick(time) {}

        float strength;
        float angle;
        float t = 0;
        float tick;
        std::chrono::time_point<std::chrono::high_resolution_clock> lastUpdate = std::chrono::high_resolution_clock::now();

        std::string getType() const override { return "BulletDrop"; }

        void show() const override { std::cout << "BulletDrop: " << std::endl; }
    };

    struct Move : public Component {
        Move(float x, float y) : x(x), y(y) {}

        float x;
        float y;

        std::string getType() const override { return "Move"; }

        void show() const override { std::cout << "Move: " << x << ", " << y << std::endl; }
    };

    struct Health : public Component {
        Health(int health) : health(health) {}

        int health;

        std::string getType() const override { return "Health"; }

        void show() const override { std::cout << "Health: " << health << std::endl; }
    };

    struct Damage : public Component {
        Damage(int damage) : damage(damage) {}

        int damage;

        std::string getType() const override { return "Damage"; }

        void show() const override { std::cout << "Damage: " << damage << std::endl; }
    };

    struct Collision : public Component {
        enum CollisionType {
            NONE = 0,
            LAMBDA = 1,
            WALL = 2,
        };

        struct CollisionInfo {
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

    struct Hitbox : public Component {
        struct intRect {
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

    struct LifeTime : public Component {
        LifeTime(int lifeTime, std::function<void(int)> callback) : lifeTime(lifeTime), callback(callback) {}

        int lifeTime;
        std::function<void(int)> callback;
        int tics = 0;

        std::string getType() const override { return "LifeTime"; }

        void show() const override { std::cout << "LifeTime: " << lifeTime << std::endl; }
    };

    struct OnKeyPressed : public Component {
        OnKeyPressed(std::function<void(int, std::vector<InputType>)> callback, size_t player = 0) : callback(callback), player(player) {}

        std::function<void(int, std::vector<InputType>)> callback;
        size_t player;
        std::chrono::time_point<std::chrono::high_resolution_clock> timer = std::chrono::high_resolution_clock::now();

        std::string getType() const override
        {
            return "OnKeyPressed";
        }

        void show() const override { std::cout << "OnKeyPressed" << std::endl; }
    };

    struct OnKeyReleased : public Component {
        OnKeyReleased(std::function<void(int, std::vector<InputType>)> callback, size_t player = 0) : callback(callback), player(player) {}

        std::function<void(int, std::vector<InputType>)> callback;
        size_t player;

        std::string getType() const override
        {
            return "OnKeyReleased";
        }

        void show() const override { std::cout << "OnKeyReleased" << std::endl; }
    };

    struct OnMousePressed : public Component {
        OnMousePressed(std::function<void(int)> callback, size_t player = 0) : callback(callback), player(player) {}

        std::function<void(int)> callback;
        size_t player;

        std::string getType() const override
        {
            return "OnMousePressed";
        }

        void show() const override { std::cout << "OnMousePressed" << std::endl; }
    };

    struct OnMouseReleased : public Component {
        OnMouseReleased(std::function<void(int)> callback, size_t player = 0) : callback(callback), player(player) {}

        std::function<void(int)> callback;
        size_t player;

        std::string getType() const override
        {
            return "OnMouseReleased";
        }

        void show() const override { std::cout << "OnMouseReleased" << std::endl; }
    };

    struct Hide : public Component {
        Hide() {}

        std::string getType() const override { return "Hide"; }

        void show() const override { std::cout << "Hide" << std::endl; }
    };

    struct Destroy : public Component {
        Destroy() {}

        std::string getType() const override { return "Destroy"; }

        void show() const override { std::cout << "Destroy" << std::endl; }
    };
}// namespace Haze
