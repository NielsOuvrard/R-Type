/*
** EPITECH PROJECT, 2023
** cpp r-type
** File description:
** Rtype.cpp
*/

#include "Rttype.hpp"
#include <haze.hpp>

Rttype::Rttype()
{
    std::cout << "hello" << std::endl;
    // engine = new Haze::Engine;
    engine.init();

    entityVortex->addComponent(new Haze::Position(120, 200));
    entityVortex->addComponent(new Haze::Velocity(2, 0));
    entityVortex->addComponent(new Haze::Size(34 * 3, 34 * 3));
    entityVortex->addComponent(vortexSprite);
    entityVortex->addComponent(new Haze::Animation(*vortexSprite, 0, 0, 34, 34, 3, 1));

    entitySpaceship->addComponent(velocityPlayer);
    entitySpaceship->addComponent(new Haze::Position(100, 200));

    entitySpaceship->addComponent(new Haze::Size(33 * 3, 18 * 3));
    entitySpaceship->addComponent(spaceshipSprite);
    entitySpaceship->addComponent(new Haze::Animation(*spaceshipSprite, 100, 0, 33, 18, 5, 1, true));

    entityWall->addComponent(new Haze::Position(0, 0));
    entityWall->addComponent(new Haze::Size(960, 140));
    wallSprite->sprite.setTextureRect(sf::IntRect(0, 0, 480, 79));
    entityWall->addComponent(wallSprite);

    entityWindow->addComponent(window);
    window->window.setFramerateLimit(60);
}

Rttype::~Rttype()
{
}

void Rttype::moveUp(void *component)
{
    auto velocity = static_cast<Haze::Velocity *>(component);
    velocity->y -= 1;
}

void Rttype::moveDown(void *component)
{
    auto velocity = static_cast<Haze::Velocity *>(component);
    velocity->y += 1;
}

void Rttype::moveLeft(void *component)
{
    auto velocity = static_cast<Haze::Velocity *>(component);
    velocity->x -= 1;
}

void Rttype::moveRight(void *component)
{
    auto velocity = static_cast<Haze::Velocity *>(component);
    velocity->x += 1;
}

void Rttype::run()
{
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
}