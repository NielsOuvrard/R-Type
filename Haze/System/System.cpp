/*
** EPITECH PROJECT, 2023
** B-CPP-500-MAR-5-1-rtype-erwan.gonzales
** File description:
** System
*/

#include "System.hpp"

namespace Haze {
    void MoveSystem(ComponentList *componentList)
    {
        for (int i = 0; i < componentList->getSize(); i++) {
            if (componentList->getComponent("Position", i) != nullptr && componentList->getComponent("Velocity", i) != nullptr) {
                auto position = static_cast<Position *>(componentList->getComponent("Position", i));
                auto velocity = static_cast<Velocity *>(componentList->getComponent("Velocity", i));
                position->x += velocity->x;
                position->y += velocity->y;
            }
        }
    }

    void RenderSystem(ComponentList *componentList)
    {
        for (int i = 0; i < componentList->getSize(); i++) {
            if (componentList->getComponent("Window", i) != nullptr) {
                auto window = static_cast<Window *>(componentList->getComponent("Window", i));
                for (int j = 0; j < componentList->getSize(); j++) {
                    if (componentList->getComponent("Position", j) != nullptr && componentList->getComponent("Sprite", j) != nullptr) {
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
        for (int i = 0; i < componentList->getSize(); i++) {
            if (componentList->getComponent("Window", i) != nullptr) {
                auto window = static_cast<Window *>(componentList->getComponent("Window", i));
                window->window.display();
            }
        }
    }

    void ClearSystem(ComponentList *componentList)
    {
        for (int i = 0; i < componentList->getSize(); i++) {
            if (componentList->getComponent("Window", i) != nullptr) {
                auto window = static_cast<Window *>(componentList->getComponent("Window", i));
                window->window.clear();
            }
        }
    }

    // void InputsSystem(std::vector<std::unique_ptr<Entity>> &entities, std::string input)
    // {
    //     for (auto &entity : entities) {
    //         if (entity->hasComponent("Inputs")) {
    //             auto window = static_cast<Window *>(entity->GetComponent("Window"));
    //             window->window.display();
    //         }
    //     }
    // }

    void VelocityOnClickSystem(ComponentList *componentList, std::string input)
    {
        for (int i = 0; i < componentList->getSize(); i++) {
            if (componentList->getComponent("VelocityOnClick", i) != nullptr && componentList->getComponent("Position", i) != nullptr) {
                std::cout << "test" << std::endl;
                auto velocityOnClick = static_cast<VelocityOnClick *>(componentList->getComponent("VelocityOnClick", i));
                auto position = static_cast<Position *>(componentList->getComponent("Position", i));
                if (input == velocityOnClick->diretionBot[0]) {
                    position->x += std::stof(velocityOnClick->diretionBot[1]);
                    position->y += std::stof(velocityOnClick->diretionBot[2]);
                }
                if (input == velocityOnClick->diretionTop[0]) {
                    position->x += std::stof(velocityOnClick->diretionTop[1]);
                    position->y += std::stof(velocityOnClick->diretionTop[2]);
                }
                if (input == velocityOnClick->diretionLeft[0]) {
                    position->x += std::stof(velocityOnClick->diretionLeft[1]);
                    position->y += std::stof(velocityOnClick->diretionLeft[2]);
                }
                if (input == velocityOnClick->diretionRight[0]) {
                    position->x += std::stof(velocityOnClick->diretionRight[1]);
                    position->y += std::stof(velocityOnClick->diretionRight[2]);
                }
            }
        }
    }

    void ColisionSystem(ComponentList *componentList)
    {
    }
}