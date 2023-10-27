#pragma once
#include "Component.hpp"
#include "inputs.hpp"
#include "json.hpp"
#include "SfDisplay.hpp"
#include <SFML/Graphics.hpp>
#include <fstream>
#include <iostream>
#include <thread>

namespace Haze {
    struct Sprite : public Component {
        Sprite(std::string path) : path(path), sprite(path) {}
        std::string path;
        SfSprite sprite;
        std::string getType() const override { return "Sprite"; }
        void show() const override { std::cout << "flm" << path << std::endl; }
    };

    struct Animation : public Component {
        struct intRect {
            int x;
            int y;
            int width;
            int height;
        };

        enum AnimationType {
            LOOP,
            BOOMERANG,
            ONCE,
            LOOP_ONCE,
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

            // * parse the json string into variables
            tics = jsonData["tics"];
            if (jsonData["type"] == "loop")
                type = AnimationType::LOOP;
            else if (jsonData["type"] == "boomerang")
                type = AnimationType::BOOMERANG;
            else if (jsonData["type"] == "once")
                type = AnimationType::ONCE;
            else if (jsonData["type"] == "loop_once")
                type = AnimationType::LOOP_ONCE;
            else
                type = AnimationType::LOOP;
            nlohmann::json animation = jsonData["animation"];

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

    struct SpriteCropped : public Component {
        SpriteCropped(uint8_t id) : frameId(id)
        {
        }

        uint8_t frameId;

        std::string getType() const override { return "SpriteCropped"; }

        void show() const override { std::cout << "SpriteCropped: " << std::endl; }
    };

    struct Window : public Component {
        Window(int width, int height) : width(width), height(height), active(false), window(width, height, "R-Type") {}

        int width;
        int height;
        bool active;
        SfWindow window;

        std::string getType() const override { return "Window"; }

        void show() const override { std::cout << "Window: " << width << ", " << height << std::endl; }
    };

    struct HitboxDisplay : public Component {
        HitboxDisplay() : rect(0, 0, 0, 0, SfColor::RED)
        {
            rect.setFillColor(SfColor::TRANSPARENT);
            rect.setOutlineColor(SfColor::RED);
            rect.setOutlineThickness(5);
        }
        SfRect rect;
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
        };

        Text(const std::string &text, colorHaze color, const std::string &fontname = "arial.ttf") : text(text),
            textObj(text, IColor::RED, fontname)
        {
            switch (color) {
            case RED:
                textObj.setColor(IColor::RED);
                break;
            case GREEN:
                textObj.setColor(IColor::GREEN);
                break;
            case BLUE:
                textObj.setColor(IColor::BLUE);
                break;
            case YELLOW:
                textObj.setColor(IColor::YELLOW);
                break;
            case BLACK:
                textObj.setColor(IColor::BLACK);
                break;
            case WHITE:
                textObj.setColor(IColor::WHITE);
                break;
            case MAGENTA:
                textObj.setColor(IColor::MAGENTA);
                break;
            case CYAN:
                textObj.setColor(IColor::CYAN);
                break;
            }
        }

        Text(const std::string &text, int r, int g, int b, int a, const std::string &fontname = "arial.ttf") : text(text),
            textObj(text, IColor::RED, fontname)
        {
            textObj.setColor(r, g, b, a);
        }

        std::string text;
        SfText textObj;

        std::string getType() const override { return "Text"; }

        void show() const override { std::cout << "Text: " << text << std::endl; }
    };
}// namespace Haze
