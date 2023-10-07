/*
** EPITECH PROJECT, 2023
** B-CPP-500-MAR-5-1-rtype-erwan.gonzales
** File description:
** protocol
*/

#pragma once

#include "Component.hpp"
#include "inputs.hpp"
#include <vector>

namespace Haze {
    struct info_inputs {
        std::vector<InputType> inputsPressed;
        std::vector<InputType> inputsReleased;
        MouseType mouseType;
        int x;
        int y;
    };

    struct id_entity {
        int id;
    };

    struct id_component {
        id_entity id;
        std::string component;
    };

    struct info_entity {
        id_entity id;
        std::vector<std::string> components;
    };

    struct info_component {
        std::string component;
        std::vector<uint8_t> data = std::vector<uint8_t>(128);
    };

    struct info_entities {
        std::vector<id_entity> id;
    };
}