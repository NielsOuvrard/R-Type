/*
** EPITECH PROJECT, 2023
** B-CPP-500-MAR-5-1-rtype-erwan.gonzales
** File description:
** System
*/

#include <chrono>
#include "SystemGfx.hpp"

namespace Haze
{
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

    void RenderSystem(ComponentList *componentList)
    {
        for (int i = 0; i < componentList->getSize(); i++)
        {
            if (componentList->getComponent("Window", i) != nullptr)
            {
                auto window = static_cast<Window *>(componentList->getComponent("Window", i));
                for (int j = 0; j < componentList->getSize(); j++)
                {
                    if (componentList->getComponent("Position", j) != nullptr &&
                        componentList->getComponent("Sprite", j) != nullptr)
                    {
                        auto sprite = static_cast<Sprite *>(componentList->getComponent("Sprite", j));
                        auto position = static_cast<Position *>(componentList->getComponent("Position", j));
                        auto scale = static_cast<Scale *>(componentList->getComponent("Scale", j));
                        if (scale != nullptr)
                            sprite->sprite.setScale(scale->x, scale->y);
                        sprite->sprite.setPosition(position->x, position->y);
                        window->window.draw(sprite->sprite);
                    }

                    if (componentList->getComponent("Hitbox", j) != nullptr &&
                        componentList->getComponent("HitboxDisplay", j) != nullptr &&
                        componentList->getComponent("Position", j) != nullptr &&
                        componentList->getComponent("Scale", j) != nullptr)
                    {
                        auto hitbox = static_cast<Hitbox *>(componentList->getComponent("Hitbox", j));
                        auto hitboxDisplay = static_cast<HitboxDisplay *>(componentList->getComponent("HitboxDisplay", j));
                        auto position = static_cast<Position *>(componentList->getComponent("Position", j));
                        auto scale = static_cast<Scale *>(componentList->getComponent("Scale", j));
                        for (int k = 0; k < hitbox->hitbox.size(); k++)
                        {
                            hitboxDisplay->rect.setPosition(hitbox->hitbox[k].x * scale->x + position->x, hitbox->hitbox[k].y * scale->y + position->y);
                            hitboxDisplay->rect.setSize(sf::Vector2f(hitbox->hitbox[k].width * scale->x, hitbox->hitbox[k].height * scale->y));
                            window->window.draw(hitboxDisplay->rect);
                        }
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

    void SplitSpriteSystem(ComponentList *componentList)
    {
        for (int i = 0; i < componentList->getSize(); i++)
        {
            if (componentList->getComponent("SplitSprite", i) != nullptr &&
                componentList->getComponent("Sprite", i) != nullptr)
            {
                auto splitSprite = static_cast<SplitSprite *>(componentList->getComponent("SplitSprite", i));
                auto sprite = static_cast<Sprite *>(componentList->getComponent("Sprite", i));
                sprite->sprite.setTextureRect(sf::IntRect(splitSprite->x, splitSprite->y, splitSprite->width, splitSprite->height));
            }
        }
    }
}