//
// Created by Niels Ouvrard on 27/10/2023.
//

#pragma once

#include "EnemyData.h"
#include <cstdint>
#include <string>

struct BossData {// ? maybe 2 types
    std::string tools_path_sprite;
    std::string tools_path_json;
    std::string path_sprite;///< The path or movement pattern of the enemy.
    std::string path_json;  ///< Animation of the sprite

    HitBox hitBoxData;

    float x;
    float y;
    float tics;    ///< The number of tics for enemy behavior. // TODO remove all of them to universal 0.05 ?
    int32_t damage;///< The damage dealt by the enemy.
    int16_t life;  ///< The remaining life or health of the enemy.
};
