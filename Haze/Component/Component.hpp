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
#include <SFML/Graphics.hpp>

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

    struct Sprite : public Component
    {
        Sprite(std::string path) : path(path) //, isAnimated(false)
        {
            texture.loadFromFile(path);
            sprite.setTexture(texture);
        }
        std::string path;
        sf::Sprite sprite;
        sf::Texture texture;
        // bool isAnimated;
        std::string getType() const override { return "Sprite"; }
        void show() const override { std::cout << "flm" << path << std::endl; }
        void setTextureRect(sf::IntRect rect) { sprite.setTextureRect(rect); }
        // void setAnimated(bool animated) { isAnimated = animated; }
    };

    struct Animation : public Component
    {
        Animation(Haze::Sprite &sprite, size_t x, size_t y, size_t width, size_t height, size_t nbFramesX, size_t nbFramesY, bool boomerang = false)
            : sprite(sprite), x(x), y(y), width(width), height(height), nbFramesX(nbFramesX), nbFramesY(nbFramesY), currentFrame(0), boomerang(boomerang), moveUp(true)
        {
            sprite.setTextureRect(sf::IntRect(x, y, width, height));
            // sprite.setAnimated(true);
        }
        Haze::Sprite &sprite;
        sf::Clock clock; // will use later in another system ?
        size_t x;
        size_t y;
        size_t width;
        size_t height;
        size_t nbFramesX;
        size_t nbFramesY;
        size_t currentFrame;
        bool boomerang;
        bool moveUp;
        std::string getType() const override { return "Animation"; }
        void show() const override { std::cout << "Animation: " << std::endl; }
    }; // can compile

    struct SplitSprite : public Component
    {
        SplitSprite(Haze::Sprite &sprite, size_t x, size_t y, size_t width, size_t height)
            : sprite(sprite), x(x), y(y), width(width), height(height)
        {
            sprite.setTextureRect(sf::IntRect(x, y, width, height));
            // sprite.setAnimated(true);
        }
        Haze::Sprite &sprite;
        size_t x;
        size_t y;
        size_t width;
        size_t height;
        std::string getType() const override { return "SplitSprite"; }
        void show() const override { std::cout << "SplitSprite: " << std::endl; }
    }; // can compile

    struct Window : public Component
    {
        Window(int width, int height) : width(width), height(height)
        {
            window.create(sf::VideoMode(width, height), "R-Type");
            window.setFramerateLimit(60);
        }
        int width;
        int height;
        sf::RenderWindow window;
        std::string getType() const override { return "Window"; }
        void show() const override { std::cout << "Window: " << width << ", " << height << std::endl; }
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
