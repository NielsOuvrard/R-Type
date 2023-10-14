/*
** ooooooooo.           ooooooooooooo
** `888   `Y88.         8'   888   `8
**  888   .d88'              888      oooo    ooo oo.ooooo.   .ooooo.
**  888ooo88P'               888       `88.  .8'   888' `88b d88' `88b
**  888`88b.    8888888      888        `88..8'    888   888 888ooo888
**  888  `88b.               888         `888'     888   888 888    .o
** o888o  o888o             o888o         .8'      888bod8P' `Y8bod8P'
**                                    .o..P'       888
**                                    `Y8P'       o888o
**
** Wall
*/

#pragma onces

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