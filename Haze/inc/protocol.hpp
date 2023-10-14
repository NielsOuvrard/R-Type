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
        int32_t x;
        int32_t y;
    };

    struct id_entity {
        uint32_t id;
    };

    struct id_component {
        id_entity id;
        std::string component;
    };

    struct info_inputs_weak {
        std::array<InputType, 10> pressedInputs;
        std::array<InputType, 10> releasedInputs;
        MouseType mouseType;

        // mouse coordinates
        int32_t x;
        int32_t y;
    };

    // # Entities
    struct entity_id {
        uint32_t id;
    };

    // !Unused
    struct entity_info {
        uint32_t id;
        std::vector<std::string> components;
    };

    // !Unused
    struct entities_info {
        std::array<uint32_t, 200> ids;
    };

    // # Components
    struct component_id {
        uint32_t id;
        char name[128];
    };

    // !unused
    struct component_info {
        uint32_t id;
        char name[128];
        std::array<uint8_t, 256> data;
    };

}// namespace Haze