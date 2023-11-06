/*
** EPITECH PROJECT, 2023
** B-CPP-500-MAR-5-1-rtype-erwan.gonzales
** File description:
** componentData
*/

#pragma once
#include "Component.hpp"
#include <iostream>
#include <map>
#include <string>
#ifdef USE_SFML
#include "ComponentGfx.hpp"
#endif

namespace Haze {
    struct PositionData {
        float x;
        float y;
    };

    struct ScaleData {
        float x;
        float y;
    };

    struct VelocityData {
        float x;
        float y;
        float time;
    };

    struct SinVelocityData {
        float x;
        float time;
        float amplitude;
        float frequency;
        float offset;
    };

    struct CircleVelocityData {
        float x;
        float time;
        float radius;
        float offset;
    };

    struct MoveData {
        float x;
        float y;
    };

    struct InterpolationData {
        int framerate;
    };

    struct HealthData {
        int health;
    };

    struct DamageData {
        int damage;
    };

    struct CollisionData {
        std::string scene;
        std::map<std::string, Collision::CollisionInfo> behavior;
    };

    struct BulletDropData {
        float strength;
        float angle;
        float time;
    };

    struct HitboxData {
        Hitbox::intRect hitbox;
    };

    struct LifeTimeData {
        int lifeTime;
    };

    struct SpriteData {
        char path[128];
    };

    struct WindowData {
        int width;
        int height;
    };

    struct TextData {
        char text[128];
        uint8_t r;
        uint8_t g;
        uint8_t b;
        uint8_t a;
        char path[128];
    };

#ifdef USE_SFML
    struct AnimationData {
        char path[128];
    };

    struct AudioData {
        char path[128];
    };

    struct SpriteCroppedData {
        uint8_t id;
    };

#endif
}// namespace Haze
