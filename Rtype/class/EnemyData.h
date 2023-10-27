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
struct EnemyData {
    // * For Animation
    std::string path_sprite;///< The path or movement pattern of the enemy.

    // did we need this ?
    std::string animation_type;/// ? "loop", "boomerang", "once", "loop_once"
    float animation_tics;

    // TODO hitbox

    int16_t x;
    int16_t y;
    int16_t tics;    ///< The number of tics for enemy behavior.
    int16_t type;    ///< The type or category of the enemy.
    int16_t damage;  ///< The damage dealt by the enemy.
    int16_t life;    ///< The remaining life or health of the enemy.
    float velocity_x;///< The horizontal velocity of the enemy.
    float velocity_y;///< The vertical velocity of the enemy.

    // ? "sinusoidal" ; "circle" ; "line"
    std::string move;     ///< The movement description or pattern of the enemy.
    std::string path_json;///< The movement description or pattern of the enemy.
    int16_t radius;       ///< The radius or size of the enemy.
};
