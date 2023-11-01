//
// Created by Niels Ouvrard on 31/10/2023.
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