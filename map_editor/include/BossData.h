//
// Created by Niels Ouvrard on 27/10/2023.
//

#pragma once

#include "Hitbox.h"
#include <cstdint>
#include <string>

struct BossData { // ? maybe 2 types
    uint16_t type;///< The type of the boss.
    std::string tools_path_sprite;
    std::string tools_path_json;
    std::string path_sprite;///< The path or movement pattern of the boss.
    std::string path_json;  ///< Animation of the sprite
    std::string sound_spawn;
    std::string sound_death;
    std::string sound_damage;

    HitBox hitBoxData;

    float x;
    float y;
    float tics;    ///< The number of tics for boss behavior. // TODO remove all of them to universal 0.05 ?
    int32_t damage;///< The damage dealt by the boss.
    int16_t life;  ///< The remaining life or health of the boss.
};
