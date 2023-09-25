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
#include "Component.hpp"


void moveUp(void *component)
{
    auto velocity = static_cast<Haze::Velocity *>(component);
    velocity->y -= 1;
}

void moveDown(void *component)
{
    auto velocity = static_cast<Haze::Velocity *>(component);
    velocity->y += 1;
}

void moveLeft(void *component)
{
    auto velocity = static_cast<Haze::Velocity *>(component);
    velocity->x -= 1;
}

void moveRight(void *component)
{
    auto velocity = static_cast<Haze::Velocity *>(component);
    velocity->x += 1;
}

int main()
{
    Haze::Engine engine;
    engine.init();
    Haze::Entity *entityVortex = engine.createEntity();
    Haze::Entity *entitySpaceship = engine.createEntity();
    Haze::Entity *entityWindow = engine.createEntity();
    Haze::Entity *entityWall = engine.createEntity();

    entityVortex->addComponent(new Haze::Position(120, 200));
    entityVortex->addComponent(new Haze::Velocity(2, 0));
    entityVortex->addComponent(new Haze::Size(34 * 3, 34 * 3));
    Haze::Sprite *vortexSprite = new Haze::Sprite("assets/r-typesheet30a.gif");
    entityVortex->addComponent(vortexSprite);
    entityVortex->addComponent(new Haze::Animation(*vortexSprite, 0, 0, 34, 34, 3, 1));

    Haze::Velocity *velocityPlayer = new Haze::Velocity(0, 0);
    entitySpaceship->addComponent(velocityPlayer);
    entitySpaceship->addComponent(new Haze::Position(100, 200));

    entitySpaceship->addComponent(new Haze::Size(33 * 3, 18 * 3));
    Haze::Sprite *spaceshipSprite = new Haze::Sprite("assets/r-typesheet1.gif");
    entitySpaceship->addComponent(spaceshipSprite);
    entitySpaceship->addComponent(new Haze::Animation(*spaceshipSprite, 100, 0, 33, 18, 5, 1, true));

    entityWall->addComponent(new Haze::Position(0, 0));
    entityWall->addComponent(new Haze::Size(960, 140));
    Haze::Sprite *wallSprite = new Haze::Sprite("assets/wall.png");
    wallSprite->sprite.setTextureRect(sf::IntRect(0, 0, 480, 79));
    entityWall->addComponent(wallSprite);
    // entityWall->addComponent(new Haze::Collision(*wallSprite));

    Haze::Window *window = new Haze::Window(800, 600);
    entityWindow->addComponent(window);

    char isMoving = '\0';

    while (engine.isOpen())
    {
        sf::Event event;
        if (!isMoving)
        {
            velocityPlayer->x = 0;
            velocityPlayer->y = 0;
        }
        else if (isMoving == 'U')
        {
            velocityPlayer->y += -1;
        }
        else if (isMoving == 'D')
        {
            velocityPlayer->y += 1;
        }
        else if (isMoving == 'L')
        {
            velocityPlayer->x += -1;
        }
        else if (isMoving == 'R')
        {
            velocityPlayer->x += 1;
        }
        while (window->window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window->window.close();
            }
            if (event.key.code == sf::Keyboard::Enter)
            {
                Haze::Entity *newVortex = engine.createEntity();
                auto position = static_cast<Haze::Position *>(entitySpaceship->getComponent("Position"));
                newVortex->addComponent(new Haze::Position(position->x, position->y));
                newVortex->addComponent(new Haze::Velocity(2, 0));
                newVortex->addComponent(new Haze::Size(34 * 3, 34 * 3));
                newVortex->addComponent(vortexSprite);
                newVortex->addComponent(new Haze::Animation(*vortexSprite, 0, 0, 34, 34, 3, 1));
            }

            // keypressed
            if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Up)
                {
                    isMoving = 'U';
                }
                if (event.key.code == sf::Keyboard::Left)
                {
                    isMoving = 'L';
                }
                if (event.key.code == sf::Keyboard::Down)
                {
                    isMoving = 'D';
                }
                if (event.key.code == sf::Keyboard::Right)
                {
                    isMoving = 'R';
                }
            }
            // keyreleased
            if (event.type == sf::Event::KeyReleased)
            {
                if (event.key.code == sf::Keyboard::Up)
                    isMoving = '\0';
                if (event.key.code == sf::Keyboard::Left)
                    isMoving = '\0';
                if (event.key.code == sf::Keyboard::Down)
                    isMoving = '\0';
                if (event.key.code == sf::Keyboard::Right)
                    isMoving = '\0';
            }
        }
        engine.update();
    }
    return 0;
}
