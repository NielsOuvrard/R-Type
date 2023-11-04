#pragma once
#include "Component.hpp"
#include "DynLib.hpp"
#include "IDisplay.hpp"
#include "inputs.hpp"
#include "json.hpp"
#include <filesystem>
#include <fstream>
#include <functional>
#include <iostream>
#include <thread>

namespace Haze {
    void setGfxLib(int lib);
    struct Sprite : public Component {
        Sprite(std::string path);

        ~Sprite()
        {
            delete sprite;
        }

        std::string path;
        ISprite *sprite;

        std::string getType() const override { return "Sprite"; }

        void show() const override { std::cout << "flm" << path << std::endl; }
    };

    struct Audio : public Component {
        Audio(std::string path);

        ~Audio()
        {
            delete audio;
        }

        std::string path;
        IAudio *audio;

        std::string getType() const override { return "Audio"; }

        void show() const override { std::cout << "Audio: " << path << std::endl; }
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
            tics = jsonData["animation_tics"];
            if (jsonData["animation_type"] == "loop")
                type = AnimationType::LOOP;
            else if (jsonData["animation_type"] == "boomerang")
                type = AnimationType::BOOMERANG;
            else if (jsonData["animation_type"] == "once")
                type = AnimationType::ONCE;
            else if (jsonData["animation_type"] == "loop_once")
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
        Window(int width, int height);

        ~Window()
        {
            delete window;
        }

        int width;
        int height;
        bool active;
        IWindow *window;

        std::string getType() const override { return "Window"; }

        void show() const override { std::cout << "Window: " << width << ", " << height << std::endl; }
    };

    struct HitboxDisplay : public Component {
        HitboxDisplay();

        ~HitboxDisplay()
        {
            delete rect;
        }

        IRect *rect;

        std::string getType() const override { return "HitboxDisplay"; }

        void show() const override { std::cout << "HitboxDisplay: " << std::endl; }
    };

    struct Sound : public Component {
        Sound(std::string path, bool loop = false);

        ~Sound()
        {
            delete sound;
        }

        std::string path;
        IAudio *sound;

        void play() { sound->play(); }

        void stop() { sound->stop(); }

        bool isPlaying() const { return sound->isPlaying(); }

        bool isStopped() const { return sound->isStopped(); }

        std::string getType() const override { return "Sound"; }

        void show() const override { std::cout << "Sound: " << path << std::endl; }
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

        Text(const std::string &text, colorHaze color, const std::string &fontname = "arial.ttf");

        Text(const std::string &text, int r, int g, int b, int a, const std::string &fontname = "arial.ttf");

        std::string text;
        IText *textObj;

        std::string getType() const override { return "Text"; }

        void show() const override { std::cout << "Text: " << text << std::endl; }
    };
}// namespace Haze
