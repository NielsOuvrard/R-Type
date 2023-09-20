/*
** EPITECH PROJECT, 2023
** B-CPP-500-MAR-5-1-rtype-erwan.gonzales
** File description:
** Component
*/

#pragma once
#include <string>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>

namespace Haze {
    class Component {
        public:
            virtual ~Component() {}
            virtual std::string getType() const = 0;
            virtual void show() const = 0;
    };

    struct Position : public Component {
        Position(float x, float y) : x(x), y(y) {}
        float x;
        float y;
        std::string getType() const override { return "Position"; }
        void show() const override { std::cout << "Position: " << x << ", " << y << std::endl; }
    };

    struct Velocity : public Component {
        Velocity(float x, float y) : x(x), y(y) {}
        float x;
        float y;
        std::string getType() const override { return "Velocity"; }
        void show() const override { std::cout << "Velocity: " << x << ", " << y << std::endl; }
    };

    struct Sprite : public Component {
        Sprite(std::string path, int width, int height) : path(path), width(width), height(height) {}
        std::string path;
        int width;
        int height;
        std::string getType() const override { return "Sprite"; }
        void show() const override { std::cout << "Sprite: " << path << ", " << width << ", " << height << std::endl; }
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

    struct Speed : public Component {
        Speed(int speed) : speed(speed) {}
        int speed;
        std::string getType() const override { return "Speed"; }
        void show() const override { std::cout << "Speed: " << speed << std::endl; }
    };

    struct Shoot : public Component {
        Shoot(int shoot) : shoot(shoot) {}
        int shoot;
        std::string getType() const override { return "Shoot"; }
        void show() const override { std::cout << "Shoot: " << shoot << std::endl; }
    };

    struct Enemy : public Component {
        Enemy(int enemy) : enemy(enemy) {}
        int enemy;
        std::string getType() const override { return "Enemy"; }
        void show() const override { std::cout << "Enemy: " << enemy << std::endl; }
    };

    struct Player : public Component {
        Player(int player) : player(player) {}
        int player;
        std::string getType() const override { return "Player"; }
        void show() const override { std::cout << "Player: " << player << std::endl; }
    };

    struct Boss : public Component {
        Boss(int boss) : boss(boss) {}
        int boss;
        std::string getType() const override { return "Boss"; }
        void show() const override { std::cout << "Boss: " << boss << std::endl; }
    };

    struct Projectile : public Component {
        Projectile(int projectile) : projectile(projectile) {}
        int projectile;
        std::string getType() const override { return "Projectile"; }
        void show() const override { std::cout << "Projectile: " << projectile << std::endl; }
    };

    struct Spawner : public Component {
        Spawner(int spawner) : spawner(spawner) {}
        int spawner;
        std::string getType() const override { return "Spawner"; }
        void show() const override { std::cout << "Spawner: " << spawner << std::endl; }
    };

    struct Collision : public Component {
        Collision(int collision) : collision(collision) {}
        int collision;
        std::string getType() const override { return "Collision"; }
        void show() const override { std::cout << "Collision: " << collision << std::endl; }
    };

    struct Score : public Component {
        Score(int score) : score(score) {}
        int score;
        std::string getType() const override { return "Score"; }
        void show() const override { std::cout << "Score: " << score << std::endl; }
    };

    struct Sound : public Component {
        Sound(int sound) : sound(sound) {}
        int sound;
        std::string getType() const override { return "Sound"; }
        void show() const override { std::cout << "Sound: " << sound << std::endl; }
    };
}