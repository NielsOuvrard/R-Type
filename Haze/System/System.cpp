/*
** EPITECH PROJECT, 2023
** B-CPP-500-MAR-5-1-rtype-erwan.gonzales
** File description:
** System
*/

#include "System.hpp"

namespace Haze
{
    void MoveSystem(ComponentList *componentList)
    {
        for (int i = 0; i < componentList->getSize(); i++)
        {
            if (componentList->getComponent("Position", i) != nullptr && componentList->getComponent("Velocity", i) != nullptr)
            {
                auto position = static_cast<Position *>(componentList->getComponent("Position", i));
                auto velocity = static_cast<Velocity *>(componentList->getComponent("Velocity", i));
                position->x += velocity->x;
                position->y += velocity->y;
            }
        }
    }

    void RenderSystem(ComponentList *componentList)
    {
        for (int i = 0; i < componentList->getSize(); i++)
        {
            if (componentList->getComponent("Window", i) != nullptr)
            {
                auto window = static_cast<Window *>(componentList->getComponent("Window", i));
                for (int j = 0; j < componentList->getSize(); j++)
                {
                    if (componentList->getComponent("Position", j) != nullptr && componentList->getComponent("Sprite", j) != nullptr)
                    {
                        auto position = static_cast<Position *>(componentList->getComponent("Position", j));
                        auto sprite = static_cast<Sprite *>(componentList->getComponent("Sprite", j));
                        sprite->sprite.setPosition(position->x, position->y);
                        window->window.draw(sprite->sprite);
                    }
                }
            }
        }
    }

    void DisplaySystem(ComponentList *componentList)
    {
        for (int i = 0; i < componentList->getSize(); i++)
        {
            if (componentList->getComponent("Window", i) != nullptr)
            {
                auto window = static_cast<Window *>(componentList->getComponent("Window", i));
                window->window.display();
            }
        }
    }

    void ClearSystem(ComponentList *componentList)
    {
        for (int i = 0; i < componentList->getSize(); i++)
        {
            if (componentList->getComponent("Window", i) != nullptr)
            {
                auto window = static_cast<Window *>(componentList->getComponent("Window", i));
                window->window.clear();
            }
        }
    }

    // only according to the position, no velocity, speed neither
    void ColisionSystem(ComponentList *componentList)
    {
        for (int i = 0; i < componentList->getSize(); i++)
        {
            if (componentList->getComponent("Position", i) != nullptr && componentList->getComponent("Collision", i) != nullptr)
            {
                auto position1 = static_cast<Position *>(componentList->getComponent("Position", i));
                auto size1 = static_cast<Size *>(componentList->getComponent("Size", i));
                auto colision1 = static_cast<Collision *>(componentList->getComponent("Collision", i));

                for (int j = 0; j < componentList->getSize(); j++)
                {
                    // check the same
                    if (i == j)
                        continue;
                    if (componentList->getComponent("Position", j) != nullptr && componentList->getComponent("Collision", j) != nullptr)
                    {
                        auto position2 = static_cast<Position *>(componentList->getComponent("Position", j));
                        auto size2 = static_cast<Size *>(componentList->getComponent("Size", j));
                        auto colision2 = static_cast<Collision *>(componentList->getComponent("Collision", j));

                        if (position1->x < position2->x + size2->width &&
                            position1->x + size1->width > position2->x &&
                            position1->y < position2->y + size2->height &&
                            position1->y + size1->height > position2->y)
                        {
                            std::cout << "COLISION" << std::endl;
                            colision1->colision = j;
                            colision2->colision = i;
                        }
                    }
                }
            }
        }
    }
}