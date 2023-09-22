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
** main
*/

#include "GraphicClient.hpp"
#include <haze.hpp>

int main()
{
    Haze::Engine engine;
    engine.init();
    Haze::Entity *entityVortex = engine.createEntity();
    Haze::Entity *entitySpaceship = engine.createEntity();
    Haze::Entity *entityWindow = engine.createEntity();

    entityVortex->addComponent(new Haze::Position(120, 200));
    // entityVortex->addComponent(new Haze::Sprite("assets/ship.png"));
    entityVortex->addComponent(new Haze::Velocity(2, 0));
    entityVortex->addComponent(new Haze::Size(34 * 3, 34 * 3));
    entityVortex->addComponent(new Haze::Animation("assets/r-typesheet30a.gif", 0, 0, 34, 34, 3, 1));

    entitySpaceship->addComponent(new Haze::Position(100, 200));
    entitySpaceship->addComponent(new Haze::Size(33 * 3, 18 * 3));
    // entitySpaceship->addComponent(new Haze::Velocity(2, 0));
    entitySpaceship->addComponent(new Haze::Animation("assets/r-typesheet1.gif", 100, 0, 33, 18, 5, 1, true));

    // std::string path, size_t width, size_t height, size_t nbFramesX, size_t nbFramesY)
    entityWindow->addComponent(new Haze::Window(800, 600));

    // 33 x 18
    // 100, 0

    while (engine.isOpen())
    {
        engine.update();
    }
    return 0;
}
