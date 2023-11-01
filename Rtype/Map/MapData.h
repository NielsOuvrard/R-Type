//
// Created by Niels Ouvrard on 31/10/2023.
//

#pragma once

#include <cstdint>
#include <string>

struct MapData {
    int16_t type;
    std::string path_json;// useless ?

    // ? Maybe
    // float velocity_x;
    // uint16_t parallax;
};
