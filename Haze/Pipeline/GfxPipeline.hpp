/*
** EPITECH PROJECT, 2023
** B-CPP-500-MAR-5-1-rtype-erwan.gonzales
** File description:
** hazeGfx
*/


#pragma once
#ifdef USE_SFML
#include "IPipeline.hpp"
#include "SystemGfx.hpp"

namespace Haze
{
    class GfxPipeline : public APipeline {
        public:
            GfxPipeline();
            ~GfxPipeline();

        protected:
        private:
    };
}
#endif
