/*
** EPITECH PROJECT, 2023
** B-CPP-500-MAR-5-1-rtype-erwan.gonzales
** File description:
** Component
*/

#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <memory>
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
        std::string getType() const override { return "Position"; }
        void show() const override { std::cout << "Position: " << x << ", " << y << std::endl; }
    };

    struct Velocity : public Component
    {
        Velocity(float x, float y) : x(x), y(y) {}
        float x;
        float y;
        std::string getType() const override { return "Velocity"; }
        void show() const override { std::cout << "Velocity: " << x << ", " << y << std::endl; }
    };

    struct VelocityOnClick : public Component
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
        Sprite(std::string path) : path(path)
        {
            texture.loadFromFile(path);
            sprite.setTexture(texture);
        }
        std::string path;
        sf::Sprite sprite;
        sf::Texture texture;
        std::string getType() const override { return "Sprite"; }
        void show() const override { std::cout << "flm" << path << std::endl; }
    };

    struct Animation : public Component
    {
        Animation(std::string path, size_t x, size_t y, size_t width, size_t height, size_t nbFramesX, size_t nbFramesY, bool boomerang = false)
            : path(path), x(x), y(y), width(width), height(height), nbFramesX(nbFramesX), nbFramesY(nbFramesY), currentFrame(0), boomerang(boomerang), moveUp(true)
        {
            texture.loadFromFile(path);
            sprite.setTexture(texture);
            sprite.setTextureRect(sf::IntRect(x, y, width, height));
        }
        std::string path;
        sf::Sprite sprite;
        sf::Texture texture;
        sf::Clock clock;
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
        void show() const override { std::cout << "Animation: " << path << std::endl; }
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

    struct Speed : public Component
    {
        Speed(int speed) : speed(speed) {}
        int speed;
        std::string getType() const override { return "Speed"; }
        void show() const override { std::cout << "Speed: " << speed << std::endl; }
    };

    struct Shoot : public Component
    {
        Shoot(int shoot) : shoot(shoot) {}
        int shoot;
        std::string getType() const override { return "Shoot"; }
        void show() const override { std::cout << "Shoot: " << shoot << std::endl; }
    };

    struct Inputs : public Component
    {
        Inputs(int inputs) : inputs(inputs) {}
        int inputs;
        std::string getType() const override { return "Inputs"; }
        void show() const override { std::cout << "Inputs: " << inputs << std::endl; }
    };

    struct Enemy : public Component
    {
        Enemy(int enemy) : enemy(enemy)
        {
        }
        int enemy;
        std::string getType() const override { return "Enemy"; }
        void show() const override { std::cout << "Enemy: " << enemy << std::endl; }
    };

    struct Player : public Component
    {
        Player(int player) : player(player) {}
        int player;
        std::string getType() const override { return "Player"; }
        void show() const override { std::cout << "Player: " << player << std::endl; }
    };

    struct Boss : public Component
    {
        Boss(int boss) : boss(boss) {}
        int boss;
        std::string getType() const override { return "Boss"; }
        void show() const override { std::cout << "Boss: " << boss << std::endl; }
    };

    struct Projectile : public Component
    {
        Projectile(int projectile) : projectile(projectile) {}
        int projectile;
        std::string getType() const override { return "Projectile"; }
        void show() const override { std::cout << "Projectile: " << projectile << std::endl; }
    };

    struct Collision : public Component
    {
        Collision(int collision) : collision(collision) {}
        int collision;
        std::string getType() const override { return "Collision"; }
        void show() const override { std::cout << "Collision: " << collision << std::endl; }
    };

    struct Size : public Component
    {
        Size(float width, float height) : height(height), width(width) {}
        float height;
        float width;
        std::string getType() const override { return "Size"; }
        void show() const override { std::cout << "Size: " << height << ", " << width << std::endl; }
    };
}