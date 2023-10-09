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
    void ScaleSystem(ComponentList *componentList, std::vector<info_inputs> *inputs) {
        for (int i = 0; i < componentList->getSize(); i++) {
            if (componentList->getComponent("Scale", i) != nullptr && componentList->getComponent("Sprite", i) != nullptr) {
                auto scale = static_cast<Scale *>(componentList->getComponent("Scale", i));
                auto sprite = static_cast<Sprite *>(componentList->getComponent("Sprite", i));
                sprite->sprite.setScale(scale->x, scale->y);
            }
        }
    }

    void RenderSystem(ComponentList *componentList, std::vector<info_inputs> *inputs) {
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
                        sprite->sprite.setScale(scale->x, scale->y);
                        sprite->sprite.setPosition(position->x, position->y);
                        window->window.draw(sprite->sprite);
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
                            hitboxDisplay->rect.setPosition(hitbox->hitbox[k].x * scale->x + position->x, hitbox->hitbox[k].y * scale->y + position->y);
                            hitboxDisplay->rect.setSize(sf::Vector2f(hitbox->hitbox[k].width * scale->x, hitbox->hitbox[k].height * scale->y));
                            window->window.draw(hitboxDisplay->rect);
                        }
                    }

                    if (componentList->getComponent("Text", j) != nullptr &&
                        componentList->getComponent("Position", j) != nullptr &&
                        componentList->getComponent("Scale", j) != nullptr) {
                        auto text = static_cast<Text *>(componentList->getComponent("Text", j));
                        auto position = static_cast<Position *>(componentList->getComponent("Position", j));
                        auto scale = static_cast<Scale *>(componentList->getComponent("Scale", j));
                        text->textObj.setPosition(position->x, position->y);
                        text->textObj.setScale(scale->x, scale->y);
                        text->textObj.setString(text->text);
                        window->window.draw(text->textObj);
                    }
                }
            }
        }
    }

    void DisplaySystem(ComponentList *componentList, std::vector<info_inputs> *inputs) {
        for (int i = 0; i < componentList->getSize(); i++) {
            if (componentList->getComponent("Window", i) != nullptr) {
                auto window = static_cast<Window *>(componentList->getComponent("Window", i));
                window->window.display();
            }
        }
    }

    void ClearSystem(ComponentList *componentList, std::vector<info_inputs> *inputs) {
        for (int i = 0; i < componentList->getSize(); i++) {
            if (componentList->getComponent("Window", i) != nullptr) {
                auto window = static_cast<Window *>(componentList->getComponent("Window", i));
                window->window.clear();
            }
        }
    }

    void AnimateSystem(ComponentList *componentList, std::vector<info_inputs> *inputs) {
        for (int i = 0; i < componentList->getSize(); i++) {
            if (componentList->getComponent("Hide", i) != nullptr)
                continue;
            if (componentList->getComponent("Animation", i) != nullptr &&
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
                    }
                }
                sprite->sprite.setTextureRect(sf::IntRect(animation->frames[animation->currentFrame].x,
                                                          animation->frames[animation->currentFrame].y,
                                                          animation->frames[animation->currentFrame].width,
                                                          animation->frames[animation->currentFrame].height));
            }
        }
    }

    void PullEvent(ComponentList *componentList, std::vector<info_inputs> *inputs) {
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
        (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) ? (inputsPressed->push_back(InputType::KEY_A)) : void();
        (sf::Keyboard::isKeyPressed(sf::Keyboard::B)) ? (inputsPressed->push_back(InputType::KEY_B)) : void();
        (sf::Keyboard::isKeyPressed(sf::Keyboard::C)) ? (inputsPressed->push_back(InputType::KEY_C)) : void();
        (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) ? (inputsPressed->push_back(InputType::KEY_D)) : void();
        (sf::Keyboard::isKeyPressed(sf::Keyboard::E)) ? (inputsPressed->push_back(InputType::KEY_E)) : void();
        (sf::Keyboard::isKeyPressed(sf::Keyboard::F)) ? (inputsPressed->push_back(InputType::KEY_F)) : void();
        (sf::Keyboard::isKeyPressed(sf::Keyboard::G)) ? (inputsPressed->push_back(InputType::KEY_G)) : void();
        (sf::Keyboard::isKeyPressed(sf::Keyboard::H)) ? (inputsPressed->push_back(InputType::KEY_H)) : void();
        (sf::Keyboard::isKeyPressed(sf::Keyboard::I)) ? (inputsPressed->push_back(InputType::KEY_I)) : void();
        (sf::Keyboard::isKeyPressed(sf::Keyboard::J)) ? (inputsPressed->push_back(InputType::KEY_J)) : void();
        (sf::Keyboard::isKeyPressed(sf::Keyboard::K)) ? (inputsPressed->push_back(InputType::KEY_K)) : void();
        (sf::Keyboard::isKeyPressed(sf::Keyboard::L)) ? (inputsPressed->push_back(InputType::KEY_L)) : void();
        (sf::Keyboard::isKeyPressed(sf::Keyboard::M)) ? (inputsPressed->push_back(InputType::KEY_M)) : void();
        (sf::Keyboard::isKeyPressed(sf::Keyboard::N)) ? (inputsPressed->push_back(InputType::KEY_N)) : void();
        (sf::Keyboard::isKeyPressed(sf::Keyboard::O)) ? (inputsPressed->push_back(InputType::KEY_O)) : void();
        (sf::Keyboard::isKeyPressed(sf::Keyboard::P)) ? (inputsPressed->push_back(InputType::KEY_P)) : void();
        (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) ? (inputsPressed->push_back(InputType::KEY_Q)) : void();
        (sf::Keyboard::isKeyPressed(sf::Keyboard::R)) ? (inputsPressed->push_back(InputType::KEY_R)) : void();
        (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) ? (inputsPressed->push_back(InputType::KEY_S)) : void();
        (sf::Keyboard::isKeyPressed(sf::Keyboard::T)) ? (inputsPressed->push_back(InputType::KEY_T)) : void();
        (sf::Keyboard::isKeyPressed(sf::Keyboard::U)) ? (inputsPressed->push_back(InputType::KEY_U)) : void();
        (sf::Keyboard::isKeyPressed(sf::Keyboard::V)) ? (inputsPressed->push_back(InputType::KEY_V)) : void();
        (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) ? (inputsPressed->push_back(InputType::KEY_W)) : void();
        (sf::Keyboard::isKeyPressed(sf::Keyboard::X)) ? (inputsPressed->push_back(InputType::KEY_X)) : void();
        (sf::Keyboard::isKeyPressed(sf::Keyboard::Y)) ? (inputsPressed->push_back(InputType::KEY_Y)) : void();
        (sf::Keyboard::isKeyPressed(sf::Keyboard::Z)) ? (inputsPressed->push_back(InputType::KEY_Z)) : void();
        (sf::Keyboard::isKeyPressed(sf::Keyboard::Num0)) ? (inputsPressed->push_back(InputType::NUMKEY_0)) : void();
        (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1)) ? (inputsPressed->push_back(InputType::NUMKEY_1)) : void();
        (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2)) ? (inputsPressed->push_back(InputType::NUMKEY_2)) : void();
        (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3)) ? (inputsPressed->push_back(InputType::NUMKEY_3)) : void();
        (sf::Keyboard::isKeyPressed(sf::Keyboard::Num4)) ? (inputsPressed->push_back(InputType::NUMKEY_4)) : void();
        (sf::Keyboard::isKeyPressed(sf::Keyboard::Num5)) ? (inputsPressed->push_back(InputType::NUMKEY_5)) : void();
        (sf::Keyboard::isKeyPressed(sf::Keyboard::Num6)) ? (inputsPressed->push_back(InputType::NUMKEY_6)) : void();
        (sf::Keyboard::isKeyPressed(sf::Keyboard::Num7)) ? (inputsPressed->push_back(InputType::NUMKEY_7)) : void();
        (sf::Keyboard::isKeyPressed(sf::Keyboard::Num8)) ? (inputsPressed->push_back(InputType::NUMKEY_8)) : void();
        (sf::Keyboard::isKeyPressed(sf::Keyboard::Num9)) ? (inputsPressed->push_back(InputType::NUMKEY_9)) : void();
        (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) ? (inputsPressed->push_back(InputType::KEY_ESC)) : void();
        (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) ? (inputsPressed->push_back(InputType::KEY_ENTER_INPUT)) : void();
        (sf::Keyboard::isKeyPressed(sf::Keyboard::Backspace)) ? (inputsPressed->push_back(InputType::KEY_BACK)) : void();
        (sf::Keyboard::isKeyPressed(sf::Keyboard::Tab)) ? (inputsPressed->push_back(InputType::KEY_TAB)) : void();
        (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) ? (inputsPressed->push_back(InputType::KEY_SPACE)) : void();
        (sf::Keyboard::isKeyPressed(sf::Keyboard::F1)) ? (inputsPressed->push_back(InputType::KEY_F1)) : void();
        (sf::Keyboard::isKeyPressed(sf::Keyboard::F2)) ? (inputsPressed->push_back(InputType::KEY_F2)) : void();
        (sf::Keyboard::isKeyPressed(sf::Keyboard::F3)) ? (inputsPressed->push_back(InputType::KEY_F3)) : void();
        (sf::Keyboard::isKeyPressed(sf::Keyboard::F4)) ? (inputsPressed->push_back(InputType::KEY_F4)) : void();
        (sf::Keyboard::isKeyPressed(sf::Keyboard::F5)) ? (inputsPressed->push_back(InputType::KEY_F5)) : void();
        (sf::Keyboard::isKeyPressed(sf::Keyboard::F6)) ? (inputsPressed->push_back(InputType::KEY_F6)) : void();
        (sf::Keyboard::isKeyPressed(sf::Keyboard::F7)) ? (inputsPressed->push_back(InputType::KEY_F7)) : void();
        (sf::Keyboard::isKeyPressed(sf::Keyboard::F8)) ? (inputsPressed->push_back(InputType::KEY_F8)) : void();
        (sf::Keyboard::isKeyPressed(sf::Keyboard::F9)) ? (inputsPressed->push_back(InputType::KEY_F9)) : void();
        (sf::Keyboard::isKeyPressed(sf::Keyboard::F10)) ? (inputsPressed->push_back(InputType::KEY_F10)) : void();
        (sf::Keyboard::isKeyPressed(sf::Keyboard::F11)) ? (inputsPressed->push_back(InputType::KEY_F11)) : void();
        (sf::Keyboard::isKeyPressed(sf::Keyboard::F12)) ? (inputsPressed->push_back(InputType::KEY_F12)) : void();
        (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) ? (inputsPressed->push_back(InputType::KEY_UP_ARROW)) : void();
        (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) ? (inputsPressed->push_back(InputType::KEY_DOWN_ARROW)) : void();
        (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) ? (inputsPressed->push_back(InputType::KEY_LEFT_ARROW)) : void();
        (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) ? (inputsPressed->push_back(InputType::KEY_RIGHT_ARROW)) : void();
        (sf::Keyboard::isKeyPressed(sf::Keyboard::Period)) ? (inputsPressed->push_back(InputType::KEY_DOT)) : void();

        for (int i = 0; i < componentList->getSize(); i++) {
            if (componentList->getComponent("Window", i) != nullptr) {
                auto window = static_cast<Window *>(componentList->getComponent("Window", i));
                *x = (int) window->window.mapPixelToCoords(sf::Mouse::getPosition(window->window)).x;
                *y = (int) window->window.mapPixelToCoords(sf::Mouse::getPosition(window->window)).y;
                if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                    *mouseType = PRESSED;
                }
                while (window->window.pollEvent(window->event)) {
                    if (window->event.type == sf::Event::Closed)
                        window->window.close();
                    if (window->event.type == sf::Event::KeyReleased) {
                        switch (window->event.key.code) {
                            case sf::Keyboard::A:
                                inputsReleased->push_back(InputType::KEY_A);
                                break;
                            case sf::Keyboard::B:
                                inputsReleased->push_back(InputType::KEY_B);
                                break;
                            case sf::Keyboard::C:
                                inputsReleased->push_back(InputType::KEY_C);
                                break;
                            case sf::Keyboard::D:
                                inputsReleased->push_back(InputType::KEY_D);
                                break;
                            case sf::Keyboard::E:
                                inputsReleased->push_back(InputType::KEY_E);
                                break;
                            case sf::Keyboard::F:
                                inputsReleased->push_back(InputType::KEY_F);
                                break;
                            case sf::Keyboard::G:
                                inputsReleased->push_back(InputType::KEY_G);
                                break;
                            case sf::Keyboard::H:
                                inputsReleased->push_back(InputType::KEY_H);
                                break;
                            case sf::Keyboard::I:
                                inputsReleased->push_back(InputType::KEY_I);
                                break;
                            case sf::Keyboard::J:
                                inputsReleased->push_back(InputType::KEY_J);
                                break;
                            case sf::Keyboard::K:
                                inputsReleased->push_back(InputType::KEY_K);
                                break;
                            case sf::Keyboard::L:
                                inputsReleased->push_back(InputType::KEY_L);
                                break;
                            case sf::Keyboard::M:
                                inputsReleased->push_back(InputType::KEY_M);
                                break;
                            case sf::Keyboard::N:
                                inputsReleased->push_back(InputType::KEY_N);
                                break;
                            case sf::Keyboard::O:
                                inputsReleased->push_back(InputType::KEY_O);
                                break;
                            case sf::Keyboard::P:
                                inputsReleased->push_back(InputType::KEY_P);
                                break;
                            case sf::Keyboard::Q:
                                inputsReleased->push_back(InputType::KEY_Q);
                                break;
                            case sf::Keyboard::R:
                                inputsReleased->push_back(InputType::KEY_R);
                                break;
                            case sf::Keyboard::S:
                                inputsReleased->push_back(InputType::KEY_S);
                                break;
                            case sf::Keyboard::T:
                                inputsReleased->push_back(InputType::KEY_T);
                                break;
                            case sf::Keyboard::U:
                                inputsReleased->push_back(InputType::KEY_U);
                                break;
                            case sf::Keyboard::V:
                                inputsReleased->push_back(InputType::KEY_V);
                                break;
                            case sf::Keyboard::W:
                                inputsReleased->push_back(InputType::KEY_W);
                                break;
                            case sf::Keyboard::X:
                                inputsReleased->push_back(InputType::KEY_X);
                                break;
                            case sf::Keyboard::Y:
                                inputsReleased->push_back(InputType::KEY_Y);
                                break;
                            case sf::Keyboard::Z:
                                inputsReleased->push_back(InputType::KEY_Z);
                                break;
                            case sf::Keyboard::Num0:
                                inputsReleased->push_back(InputType::NUMKEY_0);
                                break;
                            case sf::Keyboard::Num1:
                                inputsReleased->push_back(InputType::NUMKEY_1);
                                break;
                            case sf::Keyboard::Num2:
                                inputsReleased->push_back(InputType::NUMKEY_2);
                                break;
                            case sf::Keyboard::Num3:
                                inputsReleased->push_back(InputType::NUMKEY_3);
                                break;
                            case sf::Keyboard::Num4:
                                inputsReleased->push_back(InputType::NUMKEY_4);
                                break;
                            case sf::Keyboard::Num5:
                                inputsReleased->push_back(InputType::NUMKEY_5);
                                break;
                            case sf::Keyboard::Num6:
                                inputsReleased->push_back(InputType::NUMKEY_6);
                                break;
                            case sf::Keyboard::Num7:
                                inputsReleased->push_back(InputType::NUMKEY_7);
                                break;
                            case sf::Keyboard::Num8:
                                inputsReleased->push_back(InputType::NUMKEY_8);
                                break;
                            case sf::Keyboard::Num9:
                                inputsReleased->push_back(InputType::NUMKEY_9);
                                break;
                            case sf::Keyboard::Escape:
                                inputsReleased->push_back(InputType::KEY_ESC);
                                break;
                            case sf::Keyboard::Enter:
                                inputsReleased->push_back(InputType::KEY_ENTER_INPUT);
                                break;
                            case sf::Keyboard::Backspace:
                                inputsReleased->push_back(InputType::KEY_BACK);
                                break;
                            case sf::Keyboard::Tab:
                                inputsReleased->push_back(InputType::KEY_TAB);
                                break;
                            case sf::Keyboard::Space:
                                inputsReleased->push_back(InputType::KEY_SPACE);
                                break;
                            case sf::Keyboard::F1:
                                inputsReleased->push_back(InputType::KEY_F1);
                                break;
                            case sf::Keyboard::F2:
                                inputsReleased->push_back(InputType::KEY_F2);
                                break;
                            case sf::Keyboard::F3:
                                inputsReleased->push_back(InputType::KEY_F3);
                                break;
                            case sf::Keyboard::F4:
                                inputsReleased->push_back(InputType::KEY_F4);
                                break;
                            case sf::Keyboard::F5:
                                inputsReleased->push_back(InputType::KEY_F5);
                                break;
                            case sf::Keyboard::F6:
                                inputsReleased->push_back(InputType::KEY_F6);
                                break;
                            case sf::Keyboard::F7:
                                inputsReleased->push_back(InputType::KEY_F7);
                                break;
                            case sf::Keyboard::F8:
                                inputsReleased->push_back(InputType::KEY_F8);
                                break;
                            case sf::Keyboard::F9:
                                inputsReleased->push_back(InputType::KEY_F9);
                                break;
                            case sf::Keyboard::F10:
                                inputsReleased->push_back(InputType::KEY_F10);
                                break;
                            case sf::Keyboard::F11:
                                inputsReleased->push_back(InputType::KEY_F11);
                                break;
                            case sf::Keyboard::F12:
                                inputsReleased->push_back(InputType::KEY_F12);
                                break;
                            case sf::Keyboard::Up:
                                inputsReleased->push_back(InputType::KEY_UP_ARROW);
                                break;
                            case sf::Keyboard::Down:
                                inputsReleased->push_back(InputType::KEY_DOWN_ARROW);
                                break;
                            case sf::Keyboard::Left:
                                inputsReleased->push_back(InputType::KEY_LEFT_ARROW);
                                break;
                            case sf::Keyboard::Right:
                                inputsReleased->push_back(InputType::KEY_RIGHT_ARROW);
                                break;
                            case sf::Keyboard::Period:
                                inputsReleased->push_back(InputType::KEY_DOT);
                                break;
                            default:
                                break;
                        }
                    }
                    if (window->event.type == sf::Event::MouseButtonReleased) {
                        *mouseType = RELEASED;
                    }
                }
                break;
            }
        }
    }
}// namespace Haze
