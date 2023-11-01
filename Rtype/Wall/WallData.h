//
// Created by Niels Ouvrard on 31/10/2023.
//

#pragma once

#include "Hitbox.h"
#include <cstdint>
#include <string>

struct WallData {
    // * // FROM TYPE
    int16_t type;           ///< The type or category of the wall.
    std::string path_sprite;///< The path of the sprite.
    std::string path_json;  ///< The path of the animation of the sprite.

    HitBox hitBoxData;
};
