/*
** EPITECH PROJECT, 2023
** B-CPP-500-MAR-5-1-rtype-erwan.gonzales
** File description:
** Factory
*/

#pragma once
#include <iostream>
#ifdef USE_SFML
#include "ComponentGfx.hpp"
#endif
#include "Component.hpp"
#include "componentData.hpp"

namespace Haze {
    class Factory {
    public:
        Factory();
        ~Factory();
        static Component *createComponent(std::string type, std::array<uint8_t, 256> data);

    protected:
    private:
    };
}// namespace Haze
