//
// Created by Niels Ouvrard on 27/10/2023.
//

#pragma once

#include <cstdint>
#include <string>

/**
* @struct EnemyData
*
* @brief Represents data for an enemy in json files.
*
* The `EnemyData` structure stores various attributes and properties related to enemy entities
* in the game, including their characteristics, movement patterns, and more.
*/
struct HitBox {
    uint16_t x;
    uint16_t y;
    uint16_t width;
    uint16_t height;
};

struct EnemyData {          // ? maybe 2 types
    std::string path_sprite;///< The path or movement pattern of the enemy.

    HitBox hitBoxData;

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
    float move_radius;    ///< The radius
    std::string path_json;///< The movement description or pattern of the enemy.
};
