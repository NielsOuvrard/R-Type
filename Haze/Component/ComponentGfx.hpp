/*
** EPITECH PROJECT, 2023
** B-CPP-500-MAR-5-1-rtype-erwan.gonzales
** File description:
** Component
*/

#pragma once
#include "Component.hpp"
#include "inputs.hpp"
#include "json.hpp"
#include <SFML/Graphics.hpp>
#include <fstream>
#include <iostream>
#include <thread>

namespace Haze {
    struct Sprite : public Component {
        Sprite(std::string path) : path(path)
        {
            if (!texture.loadFromFile(path)) {
                std::cout << "Error loading texture" << std::endl;
                return;
            }
            sprite.setTexture(texture);
        }

        std::string path;
        sf::Sprite sprite;
        sf::Texture texture;

        std::string getType() const override { return "Sprite"; }

        void show() const override { std::cout << "flm" << path << std::endl; }
    };

    struct Animation : public Component {
        enum AnimationType {
            LOOP,
            BOOMERANG,
            ONCE
        };

        struct intRect {
            int x;
            int y;
            int width;
            int height;
        };

        Animation(std::string path_json)
        {
            std::ifstream inputFile(path_json);
            if (!inputFile.is_open()) {
                std::cout << "Impossible d'ouvrir le fichier !" << std::endl;
                return;
            }
            // * put the json file in a string
            nlohmann::json jsonData;
            inputFile >> jsonData;
            inputFile.close();
            // * parse the json string
            nlohmann::json data = nlohmann::json::parse(jsonData);

            tics = data["tics"];
            if (data["type"] == "loop")
                type = AnimationType::LOOP;
            else if (data["type"] == "boomerang")
                type = AnimationType::BOOMERANG;
            else if (data["type"] == "once")
                type = AnimationType::ONCE;
            else
                type = AnimationType::LOOP;
            nlohmann::json animation = data["animation"];

            for (const auto &frame: animation) {
                frames.push_back(intRect({frame["x"], frame["y"], frame["width"], frame["height"]}));
            }
        }

        std::vector<intRect> frames;
        AnimationType type = AnimationType::LOOP;
        double tics;
        size_t currentFrame = 0;
        bool direction = true;
        std::chrono::time_point<std::chrono::high_resolution_clock> lastAnimation = std::chrono::high_resolution_clock::now();

        std::string getType() const override { return "Animation"; }

        void show() const override { std::cout << "Animation: " << std::endl; }
    };

    struct Window : public Component {
        Window(int width, int height) : width(width), height(height), active(false)
        {
            window.create(sf::VideoMode(width, height), "R-Type");
            window.setFramerateLimit(60);
            window.setKeyRepeatEnabled(true);
            view.reset(sf::FloatRect(0, 0, width, height));
            view.setViewport(sf::FloatRect(0, 0, 1.0f, 1.0f));
            window.setView(view);
        }

        int width;
        int height;
        bool active;
        sf::RenderWindow window;
        sf::View view;
        sf::Event event;

        std::string getType() const override { return "Window"; }

        void show() const override { std::cout << "Window: " << width << ", " << height << std::endl; }
    };

    struct HitboxDisplay : public Component {
        HitboxDisplay()
        {
            rect.setFillColor(sf::Color::Transparent);
            rect.setOutlineColor(sf::Color::Red);
            rect.setOutlineThickness(5);
        }

        sf::Color color = sf::Color::Red;
        sf::RectangleShape rect;

        std::string getType() const override { return "HitboxDisplay"; }

        void show() const override { std::cout << "HitboxDisplay: " << std::endl; }
    };

    struct Text : public Component {
        enum colorHaze {
            RED,
            GREEN,
            BLUE,
            YELLOW,
            BLACK,
            WHITE,
            MAGENTA,
            CYAN,
            TRANSPARENT,
            COLOR_COUNT
        };

        Text(const std::string &text, colorHaze color, const std::string &fontname = "arial.ttf") : text(text), color(color)
        {
            font.loadFromFile("assets/fonts/" + fontname);
            textObj.setFont(font);
            textObj.setString(text);
            switch (color) {
                case RED:
                    textObj.setFillColor(sf::Color::Red);
                    break;
                case GREEN:
                    textObj.setFillColor(sf::Color::Green);
                    break;
                case BLUE:
                    textObj.setFillColor(sf::Color::Blue);
                    break;
                case YELLOW:
                    textObj.setFillColor(sf::Color::Yellow);
                    break;
                case BLACK:
                    textObj.setFillColor(sf::Color::Black);
                    break;
                case WHITE:
                    textObj.setFillColor(sf::Color::White);
                    break;
                case MAGENTA:
                    textObj.setFillColor(sf::Color::Magenta);
                    break;
                case CYAN:
                    textObj.setFillColor(sf::Color::Cyan);
                    break;
                case TRANSPARENT:
                    textObj.setFillColor(sf::Color::Transparent);
                    break;
                default:
                    break;
            }
        }

        std::string text;
        sf::Color color;
        sf::Font font;
        sf::Text textObj;

        std::string getType() const override { return "Text"; }

        void show() const override { std::cout << "Text: " << text << std::endl; }
    };
}// namespace Haze
