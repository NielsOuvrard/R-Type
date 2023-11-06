//
// Created by Niels Ouvrard on 31/10/2023.
//

#pragma once

#include "Hitbox.h"
#include <cstdint>
#include <string>

struct ShotData {
    // * // FROM TYPE
    int16_t type;           ///< The type or category of the shot.
    std::string path_sprite;///< The path of the sprite.
    std::string path_json;  ///< The path of the animation of the sprite.
    float velocity;
    uint16_t damage;
    bool bullet_drop;
    uint16_t bullet_drop_degree;
    bool no_animation;
    std::string sound;

    // Todo: bool bonce;
    // Todo: bool laser;

    HitBox hitBoxData;

    // * // FROM MAP
    // ? more like direction ?
    float x;     ///< The position X of the shot, according to the tile where it is.
    float y;     ///< The position Y of the shot.
    int16_t tics;///< The number of tics for shot behavior. // ? not sure
};
