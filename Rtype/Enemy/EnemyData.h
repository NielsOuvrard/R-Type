//
// Created by Niels Ouvrard on 27/10/2023.
//

#pragma once

#include "Hitbox.h"
#include <cstdint>
#include <string>

struct EnemyData {          // ? maybe 2 types
    std::string path_sprite;///< The path or movement pattern of the enemy.
    std::string path_json;  ///< Animation of the sprite

    HitBox hitBoxData;
    bool fly;
    float x;
    float y;
    int16_t tics;     ///< The number of tics for enemy behavior.
    int16_t type;     ///< The type or category of the enemy.
    int16_t shot_type;///< type of shot, -1 not shot
    int32_t damage;   ///< The damage dealt by the enemy.
    int16_t life;     ///< The remaining life or health of the enemy.
    float velocity_x; ///< The horizontal velocity of the enemy.
    float velocity_y; ///< The vertical velocity of the enemy.

    // ? "sinusoidal" ; "circular" ; "linear"
    std::string move;    ///< The movement description or pattern of the enemy.
    float move_x;        ///<
    float move_time;     ///<
    float move_amplitude;///<
    float move_frequency;///<
    float move_offset;
    float move_radius;///< The radius
};
