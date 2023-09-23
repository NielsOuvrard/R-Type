/*
** EPITECH PROJECT, 2023
** B-CPP-500-MAR-5-1-rtype-erwan.gonzales
** File description:
** System
*/

#include <chrono>
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
                position->oldX = position->x;
                position->oldY = position->y;
                position->x += velocity->x;
                position->y += velocity->y;
            }
        }
    }

    void ScaleSystem(ComponentList *componentList)
    {
        for (int i = 0; i < componentList->getSize(); i++)
        {
            if (componentList->getComponent("Scale", i) != nullptr && componentList->getComponent("Sprite", i) != nullptr)
            {
                auto scale = static_cast<Scale *>(componentList->getComponent("Scale", i));
                auto sprite = static_cast<Sprite *>(componentList->getComponent("Sprite", i));
                sprite->sprite.setScale(scale->x, scale->y);
            }
        }
    }

    void EventSystem(ComponentList *componentList)
    {
        for (int i = 0; i < componentList->getSize(); i++)
        {
            if (componentList->getComponent("Window", i) != nullptr)
            {
                auto window = static_cast<Window *>(componentList->getComponent("Window", i));
                sf::Event event;
                while (window->window.pollEvent(event))
                {
                    if (event.type == sf::Event::Closed)
                    {
                        window->window.close();
                    }
                }
            }
        }
    }

    void AnimationSystem(ComponentList *componentList)
    {
        for (int i = 0; i < componentList->getSize(); i++)
        {
            // TODO : sprite ?
            // if (componentList->getComponent("Animation", i) != nullptr && componentList->getComponent("Sprite", i) != nullptr)
            if (componentList->getComponent("Animation", i) != nullptr)
            {
                auto animation = static_cast<Animation *>(componentList->getComponent("Animation", i));
                // if (animation->clock.getElapsedTime().asSeconds() > animation->speed)
                // {
                if (animation->currentFrame == animation->nbFramesX - 1)
                {
                    animation->currentFrame = 0;
                }
                else
                {
                    animation->currentFrame++;
                }
                animation->sprite.setTextureRect(sf::IntRect(animation->currentFrame * animation->width, 0, animation->width, animation->height));
                // sprite->sprite.setTextureRect(sf::IntRect(animation->currentFrame * animation->width, 0, animation->width, animation->height));
                // animation->clock.restart();
                // }
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
                    if (componentList->getComponent("Animation", j) != nullptr)
                    {
                        auto animation = static_cast<Animation *>(componentList->getComponent("Animation", j));
                        window->window.draw(animation->sprite);
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

    void VelocityOnClickSystem(ComponentList *componentList, std::string input)
    {
        for (int i = 0; i < componentList->getSize(); i++)
        {
            if (componentList->getComponent("VelocityOnClick", i) != nullptr && componentList->getComponent("Position", i) != nullptr)
            {
                auto velocityOnClick = static_cast<VelocityOnClick *>(componentList->getComponent("VelocityOnClick", i));
                auto position = static_cast<Position *>(componentList->getComponent("Position", i));
                if (input == velocityOnClick->diretionBot[0])
                {
                    position->x += std::stof(velocityOnClick->diretionBot[1]);
                    position->y += std::stof(velocityOnClick->diretionBot[2]);
                }
                if (input == velocityOnClick->diretionTop[0])
                {
                    position->x += std::stof(velocityOnClick->diretionTop[1]);
                    position->y += std::stof(velocityOnClick->diretionTop[2]);
                }
                if (input == velocityOnClick->diretionLeft[0])
                {
                    position->x += std::stof(velocityOnClick->diretionLeft[1]);
                    position->y += std::stof(velocityOnClick->diretionLeft[2]);
                }
                if (input == velocityOnClick->diretionRight[0])
                {
                    position->x += std::stof(velocityOnClick->diretionRight[1]);
                    position->y += std::stof(velocityOnClick->diretionRight[2]);
                }
            }
        }
    }

    void CollisionHandling (ComponentList *componentList, int i, int j)
    {
        if (componentList->getComponent("Collision", i) &&
            componentList->getComponent("Collision", j))
        {
            auto collision1 = static_cast<Collision *>(componentList->getComponent("Collision", i));
            auto collision2 = static_cast<Collision *>(componentList->getComponent("Collision", j));
            if (collision1->behavior.find(collision2->scene) == collision1->behavior.end() ||
                collision2->behavior.find(collision1->scene) == collision2->behavior.end())
                return;
            Collision::CollisionInfo *info1 = &(collision1->behavior[collision2->scene]);
            Collision::CollisionInfo *info2 = &(collision2->behavior[collision1->scene]);
            if ((info1->type & Collision::CollisionType::LAMBDA) != 0)
            {
                if (std::chrono::duration<double>(std::chrono::high_resolution_clock::now() - info1->lastCollision).count() > info1->tics) {
                    info1->lastCollision = std::chrono::high_resolution_clock::now();
                    info1->onCollision(i, j);
                }
            }
            if ((info2->type & Collision::CollisionType::LAMBDA) != 0)
            {
                if (std::chrono::duration<double>(std::chrono::high_resolution_clock::now() - info2->lastCollision).count() > info2->tics) {
                    info2->lastCollision = std::chrono::high_resolution_clock::now();
                    info2->onCollision(j, i);
                }
            }
        }
    }

    void CollisionSystem(ComponentList *componentList)
    {
        for (int i = 0; i < componentList->getSize(); i++)
        {
            if (componentList->getComponent("Position", i) &&
                componentList->getComponent("Size", i))
            {
                auto position1 = static_cast<Position *>(componentList->getComponent("Position", i));
                auto size1 = static_cast<Size *>(componentList->getComponent("Size", i));
                auto scale1 = static_cast<Scale *>(componentList->getComponent("Scale", i));
                int sx1 = 1, sy1 = 1;
                if (scale1 != nullptr)
                {
                    sx1 = scale1->x * size1->width;
                    sy1 = scale1->y * size1->height;
                }
                for (int j = 0; j < componentList->getSize(); j++)
                {
                    if (i == j) continue;
                    if (componentList->getComponent("Position", j) &&
                        componentList->getComponent("Size", j))
                    {
                        auto position2 = static_cast<Position *>(componentList->getComponent("Position", j));
                        auto size2 = static_cast<Size *>(componentList->getComponent("Size", j));
                        auto scale2 = static_cast<Scale *>(componentList->getComponent("Scale", j));
                        int sx2 = 1, sy2 = 1;
                        if (scale2 != nullptr)
                        {
                            sx2 = scale2->x * size2->width;
                            sy2 = scale2->y * size2->height;
                        }
                        if (position1->x < position2->x + sx2 &&
                            position1->x + sx1 > position2->x &&
                            position1->y < position2->y + sy2 &&
                            position1->y + sy1 > position2->y)
                        {
                            // std::cout << "collision" << std::endl;
                            CollisionHandling(componentList, i, j);
                        }
                    }
                }
            }
        }
    }

    void SizeSystem(ComponentList *componentList)
    {
        for (int i = 0; i < componentList->getSize(); i++)
        {
            if (componentList->getComponent("Size", i) &&
                componentList->getComponent("Sprite", i))
            {
                auto size = static_cast<Size *>(componentList->getComponent("Size", i));
                auto sprite = static_cast<Sprite *>(componentList->getComponent("Sprite", i));
                sprite->sprite.setTextureRect(sf::IntRect(0, 0, size->width, size->height));
            }
        }
    }
}