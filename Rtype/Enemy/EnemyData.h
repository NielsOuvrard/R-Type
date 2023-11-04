//
// Created by Niels Ouvrard on 27/10/2023.
//

#pragma once

#include "Hitbox.h"
#include <cstdint>
#include <string>

struct EnemyData {
    // * // FROM TYPE
    int16_t type;           ///< The type or category of the enemy.
    int32_t damage;         ///< The damage dealt by the enemy.
    int16_t shot_type;      ///< Type of shot, -1 not shot
    uint16_t explosion_type;///< Type of explosion, -1 not explosion
    std::string path_sprite;///< The path of the sprite.
    std::string path_json;  ///< The path of the animation of the sprite.
    HitBox hitBoxData;      ///< The hitbox of the enemy.
    bool fly;               ///< The enemy can fly or is on the ground. // ! default true
    uint16_t height;

    // * // FROM MAP
    float x;         ///< The position X of the enemy, according to the tile where it is.
    float y;         ///< The position Y of the enemy.
    int16_t tics;    ///< The number of tics for enemy behavior.
    int16_t life;    ///< The remaining life or health of the enemy.
    float velocity_x;///< The horizontal velocity of the enemy.
    float velocity_y;///< The vertical velocity of the enemy.
    // move
    std::string move;    ///< The movement description or pattern of the enemy.
    float move_x;        ///< The horizontal movement of the enemy.
    float move_time;     ///< The time of the movement.
    float move_amplitude;///< The amplitude of the movement. For sinusoidal.
    float move_frequency;///< The frequency of the movement. For circle and sinusoidal.
    float move_offset;   ///< The offset of the movement. Only for circle.
    float move_radius;   ///< The radius. For circle and sinusoidal.
};
