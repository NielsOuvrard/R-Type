//
// Created by Niels Ouvrard on 31/10/2023.
//

#pragma once

#include <cstdint>
#include <string>

struct ExplosionData {
    // * // FROM TYPE
    int16_t type;           ///< The type or category of the
    std::string path_sprite;///< The path of the sprite.
    std::string path_json;  ///< The path of the animation of the sprite.

    // * // FROM MAP
    float x;     ///< The position X of the
    float y;     ///< The position Y of the
    int16_t tics;///< The number of tics for enemy behavior. // ? not sure
};
