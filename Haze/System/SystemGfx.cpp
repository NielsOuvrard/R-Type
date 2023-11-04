/*
** EPITECH PROJECT, 2023
** B-CPP-500-MAR-5-1-rtype-erwan.gonzales
** File description:
** System
*/

#include "SystemGfx.hpp"
#include "inputs.hpp"
#include <chrono>

namespace Haze {
    void ScaleSystem(ComponentList *componentList, std::vector<info_inputs> *inputs)
    {
        for (int i = 0; i < componentList->getSize(); i++) {
            if (componentList->getComponent("Scale", i) != nullptr && componentList->getComponent("Sprite", i) != nullptr) {
                auto scale = static_cast<Scale *>(componentList->getComponent("Scale", i));
                auto sprite = static_cast<Sprite *>(componentList->getComponent("Sprite", i));
                sprite->sprite->setScale(scale->x, scale->y);
            }
        }
    }

    void RenderSystem(ComponentList *componentList, std::vector<info_inputs> *inputs)
    {
        for (int i = 0; i < componentList->getSize(); i++) {
            if (componentList->getComponent("Window", i) != nullptr) {
                auto window = static_cast<Window *>(componentList->getComponent("Window", i));
                for (int j = 0; j < componentList->getSize(); j++) {
                    if (componentList->getComponent("Hide", j) != nullptr)
                        continue;
                    if (componentList->getComponent("Position", j) != nullptr &&
                        componentList->getComponent("Sprite", j) != nullptr &&
                        componentList->getComponent("Scale", j) != nullptr) {
                        auto sprite = static_cast<Sprite *>(componentList->getComponent("Sprite", j));
                        auto position = static_cast<Position *>(componentList->getComponent("Position", j));
                        auto scale = static_cast<Scale *>(componentList->getComponent("Scale", j));
                        sprite->sprite->setScale(scale->x, scale->y);
                        sprite->sprite->setPosition(position->x, position->y);
                        window->window->draw(sprite->sprite);
                    }

                    if (componentList->getComponent("Hitbox", j) != nullptr &&
                        componentList->getComponent("HitboxDisplay", j) != nullptr &&
                        componentList->getComponent("Position", j) != nullptr &&
                        componentList->getComponent("Scale", j) != nullptr) {
                        auto hitbox = static_cast<Hitbox *>(componentList->getComponent("Hitbox", j));
                        auto hitboxDisplay = static_cast<HitboxDisplay *>(componentList->getComponent("HitboxDisplay", j));
                        auto position = static_cast<Position *>(componentList->getComponent("Position", j));
                        auto scale = static_cast<Scale *>(componentList->getComponent("Scale", j));
                        for (int k = 0; k < hitbox->hitbox.size(); k++) {
                            hitboxDisplay->rect->setPosition(hitbox->hitbox[k].x * scale->x + position->x, hitbox->hitbox[k].y * scale->y + position->y);
                            hitboxDisplay->rect->setSize(hitbox->hitbox[k].width * scale->x, hitbox->hitbox[k].height * scale->y);
                            window->window->draw(hitboxDisplay->rect);
                        }
                    }

                    if (componentList->getComponent("Text", j) != nullptr &&
                        componentList->getComponent("Position", j) != nullptr &&
                        componentList->getComponent("Scale", j) != nullptr) {
                        auto text = static_cast<Text *>(componentList->getComponent("Text", j));
                        auto position = static_cast<Position *>(componentList->getComponent("Position", j));
                        auto scale = static_cast<Scale *>(componentList->getComponent("Scale", j));
                        text->textObj->setPosition(position->x, position->y);
                        text->textObj->setScale(scale->x, scale->y);
                        text->textObj->setString(text->text);
                        window->window->draw(text->textObj);
                    }
                }
            }
        }
    }

    void DisplaySystem(ComponentList *componentList, std::vector<info_inputs> *inputs)
    {
        for (int i = 0; i < componentList->getSize(); i++) {
            if (componentList->getComponent("Window", i) != nullptr) {
                auto window = static_cast<Window *>(componentList->getComponent("Window", i));
                window->window->display();
            }
        }
    }

    void ClearSystem(ComponentList *componentList, std::vector<info_inputs> *inputs)
    {
        for (int i = 0; i < componentList->getSize(); i++) {
            if (componentList->getComponent("Window", i) != nullptr) {
                auto window = static_cast<Window *>(componentList->getComponent("Window", i));
                window->window->clear();
            }
        }
    }

    void AnimateSystem(ComponentList *componentList, std::vector<info_inputs> *inputs)
    {
        for (int i = 0; i < componentList->getSize(); i++) {
            if (componentList->getComponent("Hide", i) != nullptr)
                continue;
            if (componentList->getComponent("Animation", i) != nullptr &&
                componentList->getComponent("SpriteCropped", i) != nullptr &&
                componentList->getComponent("Sprite", i) != nullptr) {
                auto animation = static_cast<Animation *>(componentList->getComponent("Animation", i));
                auto sprite_id = static_cast<SpriteCropped *>(componentList->getComponent("SpriteCropped", i));
                auto sprite = static_cast<Sprite *>(componentList->getComponent("Sprite", i));
                sprite->sprite->setTextureRect(animation->frames[sprite_id->frameId].x,
                                               animation->frames[sprite_id->frameId].y,
                                               animation->frames[sprite_id->frameId].width,
                                               animation->frames[sprite_id->frameId].height);
            } else if (componentList->getComponent("Animation", i) != nullptr &&
                       componentList->getComponent("Sprite", i) != nullptr) {
                auto animation = static_cast<Animation *>(componentList->getComponent("Animation", i));
                auto sprite = static_cast<Sprite *>(componentList->getComponent("Sprite", i));
                if (std::chrono::duration<double>(std::chrono::high_resolution_clock::now() - animation->lastAnimation).count() > animation->tics) {
                    animation->lastAnimation = std::chrono::high_resolution_clock::now();
                    if (animation->type == Animation::BOOMERANG) {
                        if (animation->direction == true) {
                            animation->currentFrame++;
                        } else {
                            animation->currentFrame--;
                        }
                        if (animation->currentFrame == animation->frames.size() - 1) {
                            animation->direction = false;
                        } else if (animation->currentFrame == 0) {
                            animation->direction = true;
                        }
                    } else if (animation->type == Animation::LOOP) {
                        if (animation->direction == true) {
                            animation->currentFrame++;
                        } else {
                            animation->currentFrame--;
                        }
                        if (animation->currentFrame == animation->frames.size()) {
                            animation->currentFrame = 0;
                        }
                    } else if (animation->type == Animation::LOOP_ONCE) {
                        if (animation->currentFrame == animation->frames.size() - 1) {
                            componentList->removeEntity(i);
                            continue;
                        }
                        if (animation->direction == true) {
                            animation->currentFrame++;
                        } else {
                            animation->currentFrame--;
                        }
                    }
                }
                sprite->sprite->setTextureRect(animation->frames[animation->currentFrame].x,
                                               animation->frames[animation->currentFrame].y,
                                               animation->frames[animation->currentFrame].width,
                                               animation->frames[animation->currentFrame].height);
            }
        }
    }

    void PullEvent(ComponentList *componentList, std::vector<info_inputs> *inputs)
    {
        if (inputs->size() == 0)
            inputs->push_back({});
        std::vector<InputType> *inputsPressed = &inputs->at(0).inputsPressed;
        std::vector<InputType> *inputsReleased = &inputs->at(0).inputsReleased;
        int *x = &inputs->at(0).x;
        int *y = &inputs->at(0).y;
        MouseType *mouseType = &inputs->at(0).mouseType;

        *inputsPressed = {};
        *inputsReleased = {};
        *mouseType = MouseType::NOTHING;

        for (int i = 0; i < componentList->getSize(); i++) {
            if (componentList->getComponent("Window", i) != nullptr) {
                auto window = static_cast<Window *>(componentList->getComponent("Window", i));

                window->window->fillKeyPressed(inputsPressed);
                window->window->fillMousePosition(x, y);
                window->window->fillMousePressed(mouseType);

                while (window->window->pollEvent()) {
                    window->window->close();
                    window->window->fillKeyReleased(inputsReleased);
                    window->window->fillFocus(&window->active);
                    window->window->fillMouseReleased(mouseType);
                }
                for (int j = 0; j < inputsPressed->size(); j++) {
                    std::cout << "Pressed: " << inputsPressed->at(j) << " "<< inputsPressed->size() << std::endl;
                }
                return;
            }
        }
    }
}// namespace Haze
