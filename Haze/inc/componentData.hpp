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
    };

    struct MoveData {
        float x;
        float y;
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

#ifdef USE_SFML
    struct AnimationData {
        char path[128];
    };

    struct SpriteCropedData {
        uint8_t id;
    };

    struct TextData {
        std::string text;
        Haze::Text::colorHaze color;
    };
#endif
}// namespace Haze
