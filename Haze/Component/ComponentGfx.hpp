/*
** EPITECH PROJECT, 2023
** B-CPP-500-MAR-5-1-rtype-erwan.gonzales
** File description:
** Component
*/

#pragma once
#include "Component.hpp"
#include <iostream>
#include <SFML/Graphics.hpp>
#include <thread>

namespace Haze
{
    struct Animation;
}

static void animateThread(int interval_ms, int duration_sec, Haze::Animation *animation);

namespace Haze
{
    struct Sprite : public Component
    {
        Sprite(std::string path) : path(path)
        {
            std::cout << "path " << path << std::endl;
            texture.loadFromFile(path);
            sprite.setTexture(texture);
        }
        std::string path;
        sf::Sprite sprite;
        sf::Texture texture;
        void setTextureRect(sf::IntRect rect) { sprite.setTextureRect(rect); }
        std::string getType() const override
        {
            return "Sprite";
        }
        void show() const override { std::cout << "flm" << path << std::endl; }
    };

    struct Animation : public Component
    {
        Animation(Haze::Sprite &sprite, size_t x, size_t y, size_t width, size_t height, size_t nbFramesX, size_t nbFramesY, bool boomerang = false)
            : sprite(sprite), x(x), y(y), width(width), height(height), nbFramesX(nbFramesX), nbFramesY(nbFramesY), currentFrame(0), boomerang(boomerang), moveUp(true)
        {
            sprite.setTextureRect(sf::IntRect(x, y, width, height));
            tics = 0.5;
            lastAnimation = std::chrono::high_resolution_clock::now();
            int interval_ms = 100;
            int duration_sec = 50;
            animation_thread = std::thread(animateThread, interval_ms, duration_sec, this);
            animation_thread.detach();
        }
        std::thread animation_thread;
        Haze::Sprite &sprite;
        std::chrono::time_point<std::chrono::high_resolution_clock> lastAnimation;
        double tics;
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
    };

    struct SplitSprite : public Component
    {
        SplitSprite(Haze::Sprite &sprite, size_t x, size_t y, size_t width, size_t height)
            : sprite(sprite), x(x), y(y), width(width), height(height)
        {
            sprite.setTextureRect(sf::IntRect(x, y, width, height));
        }
        Haze::Sprite &sprite;
        size_t x;
        size_t y;
        size_t width;
        size_t height;
        std::string getType() const override { return "SplitSprite"; }
        void show() const override { std::cout << "SplitSprite: " << std::endl; }
    };

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
        std::string getType() const override
        {
            return "Window";
        }
        void show() const override { std::cout << "Window: " << width << ", " << height << std::endl; }
    };

    struct HitboxDisplay : public Component
    {
        HitboxDisplay()
        {
            rect.setFillColor(sf::Color::Transparent);
            rect.setOutlineColor(sf::Color::Red);
            rect.setOutlineThickness(5);
        }
        sf::Color color = sf::Color::Red;
        sf::RectangleShape rect;

        std::string getType() const override
        {
            return "HitboxDisplay";
        }
        void show() const override { std::cout << "HitboxDisplay: " << std::endl; }
    };
}


// ? all useless with SFML
static void animateThread(int interval_ms, int duration_sec, Haze::Animation *animation)
{
    auto start_time = std::chrono::high_resolution_clock::now();
    while (true)
    {
        auto current_time = std::chrono::high_resolution_clock::now();
        auto elapsed_time = std::chrono::duration_cast<std::chrono::milliseconds>(current_time - start_time).count();

        if (elapsed_time >= duration_sec * 1000)
        {
            break; // Exit the animation loop after the specified duration
        }

        // Animate the sprite
        if (animation->boomerang)
        {
            if (animation->moveUp)
            {
                animation->currentFrame++;
            }
            else
            {
                animation->currentFrame--;
            }
            if (animation->currentFrame == animation->nbFramesX - 1)
            {
                animation->moveUp = false;
            }
            if (animation->currentFrame == 0)
            {
                animation->moveUp = true;
            }
        }
        else
        {
            if (animation->currentFrame == animation->nbFramesX - 1)
            {
                animation->currentFrame = 0;
            }
            else
            {
                animation->currentFrame++;
            }
        }
        animation->sprite.setTextureRect(sf::IntRect(animation->x + (animation->currentFrame * animation->width), animation->y, animation->width, animation->height));
        std::this_thread::sleep_for(std::chrono::milliseconds(interval_ms));
    }
}