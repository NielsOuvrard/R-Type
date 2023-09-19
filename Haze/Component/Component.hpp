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
    };

    struct Position : public Component {
        Position(float x, float y) : x(x), y(y) {}
        float x;
        float y;
        std::string getType() const override { return "Position"; }
    };

    struct Velocity : public Component {
        Velocity(float x, float y) : x(x), y(y) {}
        float x;
        float y;
        std::string getType() const override { return "Velocity"; }
    };

    struct Sprite : public Component {
        Sprite(std::string path, int width, int height) : path(path), width(width), height(height) {}
        std::string path;
        int width;
        int height;
        std::string getType() const override { return "Sprite"; }
    };

    struct Health : public Component {
        Health(int health) : health(health) {}
        int health;
        std::string getType() const override { return "Health"; }
    };

    struct Damage : public Component {
        Damage(int damage) : damage(damage) {}
        int damage;
        std::string getType() const override { return "Damage"; }
    };

    struct Speed : public Component {
        Speed(int speed) : speed(speed) {}
        int speed;
        std::string getType() const override { return "Speed"; }
    };

    struct Shoot : public Component {
        Shoot(int shoot) : shoot(shoot) {}
        int shoot;
        std::string getType() const override { return "Shoot"; }
    };

    struct Enemy : public Component {
        Enemy(int enemy) : enemy(enemy) {}
        int enemy;
        std::string getType() const override { return "Enemy"; }
    };

    struct Player : public Component {
        Player(int player) : player(player) {}
        int player;
        std::string getType() const override { return "Player"; }
    };

    struct Boss : public Component {
        Boss(int boss) : boss(boss) {}
        int boss;
        std::string getType() const override { return "Boss"; }
    };

    struct Projectile : public Component {
        Projectile(int projectile) : projectile(projectile) {}
        int projectile;
        std::string getType() const override { return "Projectile"; }
    };

    struct Spawner : public Component {
        Spawner(int spawner) : spawner(spawner) {}
        int spawner;
        std::string getType() const override { return "Spawner"; }
    };

    struct Collision : public Component {
        Collision(int collision) : collision(collision) {}
        int collision;
        std::string getType() const override { return "Collision"; }
    };

    struct Score : public Component {
        Score(int score) : score(score) {}
        int score;
        std::string getType() const override { return "Score"; }
    };

    struct Sound : public Component {
        Sound(int sound) : sound(sound) {}
        int sound;
        std::string getType() const override { return "Sound"; }
    };
}