//
// Created by Niels Ouvrard on 27/10/2023.
//

#pragma once

#include "Hitbox.h"
#include <cstdint>
#include <string>

struct EnemyData {
    // * // FROM TYPE
    int16_t type;
    int32_t damage;
    int16_t shot_type;
    uint16_t explosion_type;
    std::string path_sprite;
    std::string path_json;
    HitBox hitBoxData;
    bool fly;
    uint16_t height;
    std::string sound_spawn;
    std::string sound_death;
    std::string sound_damage;

    // * // FROM MAP
    float x;
    float y;
    int16_t tics;
    int16_t life;
    float velocity_x;
    float velocity_y;
    // move
    std::string move;
    float move_x;
    float move_time;
    float move_amplitude;
    float move_frequency;
    float move_offset;
    float move_radius;
};
