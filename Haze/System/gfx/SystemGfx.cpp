/*
** EPITECH PROJECT, 2023
** B-CPP-500-MAR-5-1-rtype-erwan.gonzales
** File description:
** System
*/

#include <chrono>
#include "SystemGfx.hpp"
#include "inputs.hpp"

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

    void PullEvent(ComponentList *componentList)
    {
        std::vector<InputType> inputsPressed;
        std::vector<InputType> inputsReleased;
        int x, y;
        int mouseType = 0;
        (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) ? (inputsPressed.push_back(InputType::KEY_A)) : void();
        (sf::Keyboard::isKeyPressed(sf::Keyboard::B)) ? (inputsPressed.push_back(InputType::KEY_B)) : void();
        (sf::Keyboard::isKeyPressed(sf::Keyboard::C)) ? (inputsPressed.push_back(InputType::KEY_C)) : void();
        (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) ? (inputsPressed.push_back(InputType::KEY_D)) : void();
        (sf::Keyboard::isKeyPressed(sf::Keyboard::E)) ? (inputsPressed.push_back(InputType::KEY_E)) : void();
        (sf::Keyboard::isKeyPressed(sf::Keyboard::F)) ? (inputsPressed.push_back(InputType::KEY_F)) : void();
        (sf::Keyboard::isKeyPressed(sf::Keyboard::G)) ? (inputsPressed.push_back(InputType::KEY_G)) : void();
        (sf::Keyboard::isKeyPressed(sf::Keyboard::H)) ? (inputsPressed.push_back(InputType::KEY_H)) : void();
        (sf::Keyboard::isKeyPressed(sf::Keyboard::I)) ? (inputsPressed.push_back(InputType::KEY_I)) : void();
        (sf::Keyboard::isKeyPressed(sf::Keyboard::J)) ? (inputsPressed.push_back(InputType::KEY_J)) : void();
        (sf::Keyboard::isKeyPressed(sf::Keyboard::K)) ? (inputsPressed.push_back(InputType::KEY_K)) : void();
        (sf::Keyboard::isKeyPressed(sf::Keyboard::L)) ? (inputsPressed.push_back(InputType::KEY_L)) : void();
        (sf::Keyboard::isKeyPressed(sf::Keyboard::M)) ? (inputsPressed.push_back(InputType::KEY_M)) : void();
        (sf::Keyboard::isKeyPressed(sf::Keyboard::N)) ? (inputsPressed.push_back(InputType::KEY_N)) : void();
        (sf::Keyboard::isKeyPressed(sf::Keyboard::O)) ? (inputsPressed.push_back(InputType::KEY_O)) : void();
        (sf::Keyboard::isKeyPressed(sf::Keyboard::P)) ? (inputsPressed.push_back(InputType::KEY_P)) : void();
        (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) ? (inputsPressed.push_back(InputType::KEY_Q)) : void();
        (sf::Keyboard::isKeyPressed(sf::Keyboard::R)) ? (inputsPressed.push_back(InputType::KEY_R)) : void();
        (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) ? (inputsPressed.push_back(InputType::KEY_S)) : void();
        (sf::Keyboard::isKeyPressed(sf::Keyboard::T)) ? (inputsPressed.push_back(InputType::KEY_T)) : void();
        (sf::Keyboard::isKeyPressed(sf::Keyboard::U)) ? (inputsPressed.push_back(InputType::KEY_U)) : void();
        (sf::Keyboard::isKeyPressed(sf::Keyboard::V)) ? (inputsPressed.push_back(InputType::KEY_V)) : void();
        (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) ? (inputsPressed.push_back(InputType::KEY_W)) : void();
        (sf::Keyboard::isKeyPressed(sf::Keyboard::X)) ? (inputsPressed.push_back(InputType::KEY_X)) : void();
        (sf::Keyboard::isKeyPressed(sf::Keyboard::Y)) ? (inputsPressed.push_back(InputType::KEY_Y)) : void();
        (sf::Keyboard::isKeyPressed(sf::Keyboard::Z)) ? (inputsPressed.push_back(InputType::KEY_Z)) : void();
        (sf::Keyboard::isKeyPressed(sf::Keyboard::Num0)) ? (inputsPressed.push_back(InputType::NUMKEY_0)) : void();
        (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1)) ? (inputsPressed.push_back(InputType::NUMKEY_1)) : void();
        (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2)) ? (inputsPressed.push_back(InputType::NUMKEY_2)) : void();
        (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3)) ? (inputsPressed.push_back(InputType::NUMKEY_3)) : void();
        (sf::Keyboard::isKeyPressed(sf::Keyboard::Num4)) ? (inputsPressed.push_back(InputType::NUMKEY_4)) : void();
        (sf::Keyboard::isKeyPressed(sf::Keyboard::Num5)) ? (inputsPressed.push_back(InputType::NUMKEY_5)) : void();
        (sf::Keyboard::isKeyPressed(sf::Keyboard::Num6)) ? (inputsPressed.push_back(InputType::NUMKEY_6)) : void();
        (sf::Keyboard::isKeyPressed(sf::Keyboard::Num7)) ? (inputsPressed.push_back(InputType::NUMKEY_7)) : void();
        (sf::Keyboard::isKeyPressed(sf::Keyboard::Num8)) ? (inputsPressed.push_back(InputType::NUMKEY_8)) : void();
        (sf::Keyboard::isKeyPressed(sf::Keyboard::Num9)) ? (inputsPressed.push_back(InputType::NUMKEY_9)) : void();
        (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) ? (inputsPressed.push_back(InputType::KEY_ESC)) : void();
        (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) ? (inputsPressed.push_back(InputType::KEY_ENTER_INPUT)) : void();
        (sf::Keyboard::isKeyPressed(sf::Keyboard::Backspace)) ? (inputsPressed.push_back(InputType::KEY_BACK)) : void();
        (sf::Keyboard::isKeyPressed(sf::Keyboard::Tab)) ? (inputsPressed.push_back(InputType::KEY_TAB)) : void();
        (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) ? (inputsPressed.push_back(InputType::KEY_SPACE)) : void();
        (sf::Keyboard::isKeyPressed(sf::Keyboard::F1)) ? (inputsPressed.push_back(InputType::KEY_F1)) : void();
        (sf::Keyboard::isKeyPressed(sf::Keyboard::F2)) ? (inputsPressed.push_back(InputType::KEY_F2)) : void();
        (sf::Keyboard::isKeyPressed(sf::Keyboard::F3)) ? (inputsPressed.push_back(InputType::KEY_F3)) : void();
        (sf::Keyboard::isKeyPressed(sf::Keyboard::F4)) ? (inputsPressed.push_back(InputType::KEY_F4)) : void();
        (sf::Keyboard::isKeyPressed(sf::Keyboard::F5)) ? (inputsPressed.push_back(InputType::KEY_F5)) : void();
        (sf::Keyboard::isKeyPressed(sf::Keyboard::F6)) ? (inputsPressed.push_back(InputType::KEY_F6)) : void();
        (sf::Keyboard::isKeyPressed(sf::Keyboard::F7)) ? (inputsPressed.push_back(InputType::KEY_F7)) : void();
        (sf::Keyboard::isKeyPressed(sf::Keyboard::F8)) ? (inputsPressed.push_back(InputType::KEY_F8)) : void();
        (sf::Keyboard::isKeyPressed(sf::Keyboard::F9)) ? (inputsPressed.push_back(InputType::KEY_F9)) : void();
        (sf::Keyboard::isKeyPressed(sf::Keyboard::F10)) ? (inputsPressed.push_back(InputType::KEY_F10)) : void();
        (sf::Keyboard::isKeyPressed(sf::Keyboard::F11)) ? (inputsPressed.push_back(InputType::KEY_F11)) : void();
        (sf::Keyboard::isKeyPressed(sf::Keyboard::F12)) ? (inputsPressed.push_back(InputType::KEY_F12)) : void();
        (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) ? (inputsPressed.push_back(InputType::KEY_UP_ARROW)) : void();
        (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) ? (inputsPressed.push_back(InputType::KEY_DOWN_ARROW)) : void();
        (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) ? (inputsPressed.push_back(InputType::KEY_LEFT_ARROW)) : void();
        (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) ? (inputsPressed.push_back(InputType::KEY_RIGHT_ARROW)) : void();

        for (int i = 0; i < componentList->getSize(); i++)
        {
            if (componentList->getComponent("Window", i) != nullptr)
            {
                auto window = static_cast<Window *>(componentList->getComponent("Window", i));
                while (window->window.pollEvent(window->event))
                {
                    if (window->event.type == sf::Event::Closed)
                        window->window.close();
                    if (window->event.type == sf::Event::KeyReleased) {
                        switch (window->event.KeyReleased) {
                            case sf::Keyboard::A:
                                inputsReleased.push_back(InputType::KEY_A);
                                break;
                            case sf::Keyboard::B:
                                inputsReleased.push_back(InputType::KEY_B);
                                break;
                            case sf::Keyboard::C:
                                inputsReleased.push_back(InputType::KEY_C);
                                break;
                            case sf::Keyboard::D:
                                inputsReleased.push_back(InputType::KEY_D);
                                break;
                            case sf::Keyboard::E:
                                inputsReleased.push_back(InputType::KEY_E);
                                break;
                            case sf::Keyboard::F:
                                inputsReleased.push_back(InputType::KEY_F);
                                break;
                            case sf::Keyboard::G:
                                inputsReleased.push_back(InputType::KEY_G);
                                break;
                            case sf::Keyboard::H:
                                inputsReleased.push_back(InputType::KEY_H);
                                break;
                            case sf::Keyboard::I:
                                inputsReleased.push_back(InputType::KEY_I);
                                break;
                            case sf::Keyboard::J:
                                inputsReleased.push_back(InputType::KEY_J);
                                break;
                            case sf::Keyboard::K:
                                inputsReleased.push_back(InputType::KEY_K);
                                break;
                            case sf::Keyboard::L:
                                inputsReleased.push_back(InputType::KEY_L);
                                break;
                            case sf::Keyboard::M:
                                inputsReleased.push_back(InputType::KEY_M);
                                break;
                            case sf::Keyboard::N:
                                inputsReleased.push_back(InputType::KEY_N);
                                break;
                            case sf::Keyboard::O:
                                inputsReleased.push_back(InputType::KEY_O);
                                break;
                            case sf::Keyboard::P:
                                inputsReleased.push_back(InputType::KEY_P);
                                break;
                            case sf::Keyboard::Q:
                                inputsReleased.push_back(InputType::KEY_Q);
                                break;
                            case sf::Keyboard::R:
                                inputsReleased.push_back(InputType::KEY_R);
                                break;
                            case sf::Keyboard::S:
                                inputsReleased.push_back(InputType::KEY_S);
                                break;
                            case sf::Keyboard::T:
                                inputsReleased.push_back(InputType::KEY_T);
                                break;
                            case sf::Keyboard::U:
                                inputsReleased.push_back(InputType::KEY_U);
                                break;
                            case sf::Keyboard::V:
                                inputsReleased.push_back(InputType::KEY_V);
                                break;
                            case sf::Keyboard::W:
                                inputsReleased.push_back(InputType::KEY_W);
                                break;
                            case sf::Keyboard::X:
                                inputsReleased.push_back(InputType::KEY_X);
                                break;
                            case sf::Keyboard::Y:
                                inputsReleased.push_back(InputType::KEY_Y);
                                break;
                            case sf::Keyboard::Z:
                                inputsReleased.push_back(InputType::KEY_Z);
                                break;
                            case sf::Keyboard::Num0:
                                inputsReleased.push_back(InputType::NUMKEY_0);
                                break;
                            case sf::Keyboard::Num1:
                                inputsReleased.push_back(InputType::NUMKEY_1);
                                break;
                            case sf::Keyboard::Num2:
                                inputsReleased.push_back(InputType::NUMKEY_2);
                                break;
                            case sf::Keyboard::Num3:
                                inputsReleased.push_back(InputType::NUMKEY_3);
                                break;
                            case sf::Keyboard::Num4:
                                inputsReleased.push_back(InputType::NUMKEY_4);
                                break;
                            case sf::Keyboard::Num5:
                                inputsReleased.push_back(InputType::NUMKEY_5);
                                break;
                            case sf::Keyboard::Num6:
                                inputsReleased.push_back(InputType::NUMKEY_6);
                                break;
                            case sf::Keyboard::Num7:
                                inputsReleased.push_back(InputType::NUMKEY_7);
                                break;
                            case sf::Keyboard::Num8:
                                inputsReleased.push_back(InputType::NUMKEY_8);
                                break;
                            case sf::Keyboard::Num9:
                                inputsReleased.push_back(InputType::NUMKEY_9);
                                break;
                            case sf::Keyboard::Escape:
                                inputsReleased.push_back(InputType::KEY_ESC);
                                break;
                            case sf::Keyboard::Enter:
                                inputsReleased.push_back(InputType::KEY_ENTER_INPUT);
                                break;
                            case sf::Keyboard::Backspace:
                                inputsReleased.push_back(InputType::KEY_BACK);
                                break;
                            case sf::Keyboard::Tab:
                                inputsReleased.push_back(InputType::KEY_TAB);
                                break;
                            case sf::Keyboard::Space:
                                inputsReleased.push_back(InputType::KEY_SPACE);
                                break;
                            case sf::Keyboard::F1:
                                inputsReleased.push_back(InputType::KEY_F1);
                                break;
                            case sf::Keyboard::F2:
                                inputsReleased.push_back(InputType::KEY_F2);
                                break;
                            case sf::Keyboard::F3:
                                inputsReleased.push_back(InputType::KEY_F3);
                                break;
                            case sf::Keyboard::F4:
                                inputsReleased.push_back(InputType::KEY_F4);
                                break;
                            case sf::Keyboard::F5:
                                inputsReleased.push_back(InputType::KEY_F5);
                                break;
                            case sf::Keyboard::F6:
                                inputsReleased.push_back(InputType::KEY_F6);
                                break;
                            case sf::Keyboard::F7:
                                inputsReleased.push_back(InputType::KEY_F7);
                                break;
                            case sf::Keyboard::F8:
                                inputsReleased.push_back(InputType::KEY_F8);
                                break;
                            case sf::Keyboard::F9:
                                inputsReleased.push_back(InputType::KEY_F9);
                                break;
                            case sf::Keyboard::F10:
                                inputsReleased.push_back(InputType::KEY_F10);
                                break;
                            case sf::Keyboard::F11:
                                inputsReleased.push_back(InputType::KEY_F11);
                                break;
                            case sf::Keyboard::F12:
                                inputsReleased.push_back(InputType::KEY_F12);
                                break;
                            case sf::Keyboard::Up:
                                inputsReleased.push_back(InputType::KEY_UP_ARROW);
                                break;
                            case sf::Keyboard::Down:
                                inputsReleased.push_back(InputType::KEY_DOWN_ARROW);
                                break;
                            case sf::Keyboard::Left:
                                inputsReleased.push_back(InputType::KEY_LEFT_ARROW);
                                break;
                            case sf::Keyboard::Right:
                                inputsReleased.push_back(InputType::KEY_RIGHT_ARROW);
                                break;
                            default:
                                break;
                        }
                    }
                    if (window->event.type == sf::Event::MouseButtonPressed) {
                        mouseType = 1;
                    }
                    if (window->event.type == sf::Event::MouseButtonReleased) {
                        mouseType = 2;
                    }
                }
                x = window->event.mouseMove.x;
                y = window->event.mouseMove.y;
            }
        }
        for (int i = 0; i < componentList->getSize(); i++) {
            if (componentList->getComponent("OnKeyPressed", i) != nullptr) {
                auto onKeyPressed = static_cast<OnKeyPressed *>(componentList->getComponent("OnKeyPressed", i));
                onKeyPressed->callback(i, inputsPressed);
            }
            if (componentList->getComponent("OnKeyReleased", i) != nullptr) {
                auto onKeyReleased = static_cast<OnKeyReleased *>(componentList->getComponent("OnKeyReleased", i));
                onKeyReleased->callback(i, inputsReleased);
            }
            if (mouseType == 1 &&
                componentList->getComponent("OnMousePressed", i) != nullptr &&
                componentList->getComponent("Position", i) != nullptr &&
                componentList->getComponent("Hitbox", i) != nullptr &&
                componentList->getComponent("Scale", i) != nullptr) {
                auto onMousePressed = static_cast<OnMousePressed *>(componentList->getComponent("OnMousePressed", i));
                auto position = static_cast<Position *>(componentList->getComponent("Position", i));
                auto hitbox = static_cast<Hitbox *>(componentList->getComponent("Hitbox", i));
                auto scale = static_cast<Scale *>(componentList->getComponent("Scale", i));
                for (int j = 0; j < hitbox->hitbox.size(); j++) {
                    if (x >= hitbox->hitbox[j].x * scale->x + position->x &&
                        x <= hitbox->hitbox[j].x * scale->x + position->x + hitbox->hitbox[j].width * scale->x &&
                        y >= hitbox->hitbox[j].y * scale->y + position->y &&
                        y <= hitbox->hitbox[j].y * scale->y + position->y + hitbox->hitbox[j].height * scale->y) {
                        onMousePressed->callback(i);
                    }
                }
            }
            if (mouseType == 2 &&
                componentList->getComponent("OnMouseReleased", i) != nullptr &&
                componentList->getComponent("Position", i) != nullptr &&
                componentList->getComponent("Hitbox", i) != nullptr &&
                componentList->getComponent("Scale", i) != nullptr) {
                auto onMouseReleased = static_cast<OnMouseReleased *>(componentList->getComponent("OnMouseReleased", i));
                auto position = static_cast<Position *>(componentList->getComponent("Position", i));
                auto hitbox = static_cast<Hitbox *>(componentList->getComponent("Hitbox", i));
                auto scale = static_cast<Scale *>(componentList->getComponent("Scale", i));
                for (int j = 0; j < hitbox->hitbox.size(); j++) {
                    if (x >= hitbox->hitbox[j].x * scale->x + position->x &&
                        x <= hitbox->hitbox[j].x * scale->x + position->x + hitbox->hitbox[j].width * scale->x &&
                        y >= hitbox->hitbox[j].y * scale->y + position->y &&
                        y <= hitbox->hitbox[j].y * scale->y + position->y + hitbox->hitbox[j].height * scale->y) {
                        onMouseReleased->callback(i);
                    }
                }
            }
        }
    }
}
