/*
** EPITECH PROJECT, 2023
** cpp r-type
** File description:
** wall.hpp
*/

#pragma once

#include <haze-core.hpp>
#include <haze-graphics.hpp>
#include "json.hpp"

class wall
{
    private:
    public:
        void changeSpriteBack(Haze::Entity *E);
        Haze::Sprite *_wallSprite = new Haze::Sprite("assets/wall.png");
        Haze::Entity *_entityWallBottom;
        nlohmann::json _sheet;
        nlohmann::json _jsonData;

        wall(Haze::Engine *engine, nlohmann::json _jsonData, int x, int y);
        ~wall();
};