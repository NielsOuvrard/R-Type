/*
** EPITECH PROJECT, 2023
** B-CPP-500-MAR-5-1-rtype-erwan.gonzales
** File description:
** System
*/

#include "SystemCore.hpp"

namespace Haze {
    void useInputs(ComponentList *componentList, std::vector<info_inputs> *inputs)
    {
        for (int i = 0; i < componentList->getSize(); i++) {
            if (componentList->getComponent("Hide", i) != nullptr)
                continue;
            if (componentList->getComponent("OnKeyPressed", i) != nullptr) {
                auto onKeyPressed = static_cast<OnKeyPressed *>(componentList->getComponent("OnKeyPressed", i));
                if (onKeyPressed->player < inputs->size()) {
                    if (inputs->at(onKeyPressed->player).inputsPressed.size() > 0)
                        onKeyPressed->callback(i, inputs->at(onKeyPressed->player).inputsPressed);
                }
            }
            if (componentList->getComponent("OnKeyReleased", i) != nullptr) {
                auto onKeyReleased = static_cast<OnKeyReleased *>(componentList->getComponent("OnKeyReleased", i));
                if (onKeyReleased->player < inputs->size()) {
                    if (inputs->at(onKeyReleased->player).inputsReleased.size() > 0)
                        onKeyReleased->callback(i, inputs->at(onKeyReleased->player).inputsReleased);
                }
            }
            if (componentList->getComponent("OnMousePressed", i) != nullptr &&
                componentList->getComponent("Position", i) != nullptr &&
                componentList->getComponent("Hitbox", i) != nullptr &&
                componentList->getComponent("Scale", i) != nullptr) {
                auto onMousePressed = static_cast<OnMousePressed *>(componentList->getComponent("OnMousePressed", i));
                auto position = static_cast<Position *>(componentList->getComponent("Position", i));
                auto hitbox = static_cast<Hitbox *>(componentList->getComponent("Hitbox", i));
                auto scale = static_cast<Scale *>(componentList->getComponent("Scale", i));

                if (onMousePressed->player < inputs->size() && inputs->at(onMousePressed->player).mouseType == PRESSED) {
                    for (int j = 0; j < hitbox->hitbox.size(); j++) {
                        if (inputs->at(onMousePressed->player).x >= hitbox->hitbox[j].x * scale->x + position->x &&
                            inputs->at(onMousePressed->player).x <= hitbox->hitbox[j].x * scale->x + position->x + hitbox->hitbox[j].width * scale->x &&
                            inputs->at(onMousePressed->player).y >= hitbox->hitbox[j].y * scale->y + position->y &&
                            inputs->at(onMousePressed->player).y <= hitbox->hitbox[j].y * scale->y + position->y + hitbox->hitbox[j].height * scale->y) {
                            onMousePressed->callback(i);
                        }
                    }
                }
            }
            if (componentList->getComponent("OnMouseReleased", i) != nullptr &&
                componentList->getComponent("Position", i) != nullptr &&
                componentList->getComponent("Hitbox", i) != nullptr &&
                componentList->getComponent("Scale", i) != nullptr) {
                auto onMouseReleased = static_cast<OnMouseReleased *>(componentList->getComponent("OnMouseReleased", i));
                auto position = static_cast<Position *>(componentList->getComponent("Position", i));
                auto hitbox = static_cast<Hitbox *>(componentList->getComponent("Hitbox", i));
                auto scale = static_cast<Scale *>(componentList->getComponent("Scale", i));
                if (onMouseReleased->player < inputs->size() && inputs->at(onMouseReleased->player).mouseType == RELEASED) {
                    for (int j = 0; j < hitbox->hitbox.size(); j++) {
                        if (inputs->at(onMouseReleased->player).x >= hitbox->hitbox[j].x * scale->x + position->x &&
                            inputs->at(onMouseReleased->player).x <= hitbox->hitbox[j].x * scale->x + position->x + hitbox->hitbox[j].width * scale->x &&
                            inputs->at(onMouseReleased->player).y >= hitbox->hitbox[j].y * scale->y + position->y &&
                            inputs->at(onMouseReleased->player).y <= hitbox->hitbox[j].y * scale->y + position->y + hitbox->hitbox[j].height * scale->y) {
                            onMouseReleased->callback(i);
                        }
                    }
                }
            }
        }
        for (int i = 0; i < inputs->size(); i++) {
            inputs->at(i).inputsPressed.clear();
            inputs->at(i).inputsReleased.clear();
        }
    }

    void MoveSystem(ComponentList *componentList, std::vector<info_inputs> *inputs)
    {
        for (int i = 0; i < componentList->getSize(); i++) {
            if (componentList->getComponent("Hide", i) != nullptr)
                continue;
            if (componentList->getComponent("Position", i) != nullptr && componentList->getComponent("Velocity", i) != nullptr) {
                auto position = static_cast<Position *>(componentList->getComponent("Position", i));
                auto velocity = static_cast<Velocity *>(componentList->getComponent("Velocity", i));
                float gap = std::chrono::duration<double>(std::chrono::high_resolution_clock::now() - velocity->lastUpdate).count();
                position->x += (velocity->x * gap) / velocity->tick;
                position->y += (velocity->y * gap) / velocity->tick;
                velocity->lastUpdate = std::chrono::high_resolution_clock::now();
            }
            if (componentList->getComponent("Position", i) != nullptr && componentList->getComponent("VelocityInterpolation", i) != nullptr) {
                auto position = static_cast<Position *>(componentList->getComponent("Position", i));
                auto velocityInterpolation = static_cast<VelocityInterpolation *>(componentList->getComponent("VelocityInterpolation", i));
                float gap = std::chrono::duration<double>(std::chrono::high_resolution_clock::now() - velocityInterpolation->lastUpdate).count();
                position->x += (velocityInterpolation->x * gap) / velocityInterpolation->tick;
                position->y += (velocityInterpolation->y * gap) / velocityInterpolation->tick;
                velocityInterpolation->lastUpdate = std::chrono::high_resolution_clock::now();
                if (std::chrono::duration<double>(std::chrono::high_resolution_clock::now() - velocityInterpolation->fullUpdate).count() > velocityInterpolation->tick)
                    componentList->removeComponent("VelocityInterpolation", i);
            }
            if (componentList->getComponent("Position", i) != nullptr && componentList->getComponent("Move", i) != nullptr) {
                auto position = static_cast<Position *>(componentList->getComponent("Position", i));
                auto move = static_cast<Move *>(componentList->getComponent("Move", i));
                position->x += move->x;
                position->y += move->y;
                componentList->removeComponent("Move", i);
            }
            if (componentList->getComponent("Position", i) != nullptr && componentList->getComponent("SinVelocity", i) != nullptr) {
                auto position = static_cast<Position *>(componentList->getComponent("Position", i));
                auto sinVelocity = static_cast<SinVelocity *>(componentList->getComponent("SinVelocity", i));
                float gap = std::chrono::duration<double>(std::chrono::high_resolution_clock::now() - sinVelocity->lastUpdate).count();
                float oldX = position->x + sinVelocity->offset;
                position->x += (sinVelocity->x * gap) / sinVelocity->tick;
                if (sinVelocity->applied) {
                    position->y -= sin(sinVelocity->frequency * oldX) * sinVelocity->amplitude;
                } else {
                    sinVelocity->applied = true;
                }
                position->y += sin(sinVelocity->frequency * position->x) * sinVelocity->amplitude;
                sinVelocity->lastUpdate = std::chrono::high_resolution_clock::now();
            }
            if (componentList->getComponent("Position", i) != nullptr && componentList->getComponent("CircleVelocity", i) != nullptr) {
                auto position = static_cast<Position *>(componentList->getComponent("Position", i));
                auto circleVelocity = static_cast<CircleVelocity *>(componentList->getComponent("CircleVelocity", i));
                float gap = std::chrono::duration<double>(std::chrono::high_resolution_clock::now() - circleVelocity->lastUpdate).count();
                float oldT = circleVelocity->t;
                circleVelocity->t += (circleVelocity->x * gap) / circleVelocity->tick;
                if (circleVelocity->applied) {
                    position->x -= cos(oldT) * circleVelocity->radius;
                    position->y -= sin(oldT) * circleVelocity->radius;
                } else {
                    circleVelocity->applied = true;
                }
                position->x += cos(circleVelocity->t) * circleVelocity->radius;
                position->y += sin(circleVelocity->t) * circleVelocity->radius;
                circleVelocity->lastUpdate = std::chrono::high_resolution_clock::now();
            }
            if (componentList->getComponent("Position", i) != nullptr && componentList->getComponent("BulletDrop", i) != nullptr) {
                auto position = static_cast<Position *>(componentList->getComponent("Position", i));
                auto bulletDrop = static_cast<BulletDrop *>(componentList->getComponent("BulletDrop", i));
                float gap = std::chrono::duration<double>(std::chrono::high_resolution_clock::now() - bulletDrop->lastUpdate).count();
                bulletDrop->t += (0.1 * gap) / 0.1;
                float X = cos(bulletDrop->angle * M_PI / 180);
                float Y = sin(bulletDrop->angle * M_PI / 180);

                float accelerationX = (cos(bulletDrop->angle * M_PI / 180) * bulletDrop->strength);
                float accelerationY = 9.81 + (sin(bulletDrop->angle * M_PI / 180) * bulletDrop->strength);

                position->x += (-((X * bulletDrop->strength) * -bulletDrop->t + 0.5 * accelerationX * bulletDrop->t * bulletDrop->t) * gap) / 0.01;
                position->y += (((Y * bulletDrop->strength) * -bulletDrop->t + 0.5 * accelerationY * bulletDrop->t * bulletDrop->t) * gap) / 0.01;
                bulletDrop->lastUpdate = std::chrono::high_resolution_clock::now();
            }
        }
    }

    void CollisionHandling(ComponentList *componentList, int i, int j)
    {
        if (componentList->getComponent("Collision", i) &&
            componentList->getComponent("Collision", j)) {
            auto collision1 = static_cast<Collision *>(componentList->getComponent("Collision", i));
            auto collision2 = static_cast<Collision *>(componentList->getComponent("Collision", j));
            if (collision1->behavior.find(collision2->scene) == collision1->behavior.end() ||
                collision2->behavior.find(collision1->scene) == collision2->behavior.end())
                return;
            Collision::CollisionInfo *info1 = &(collision1->behavior[collision2->scene]);
            Collision::CollisionInfo *info2 = &(collision2->behavior[collision1->scene]);
            if ((info1->type & Collision::CollisionType::LAMBDA) != 0) {
                if (std::chrono::duration<double>(std::chrono::high_resolution_clock::now() - info1->lastCollision).count() > info1->tics) {
                    info1->lastCollision = std::chrono::high_resolution_clock::now();
                    info1->onCollision(i, j);
                }
            }
            if ((info2->type & Collision::CollisionType::LAMBDA) != 0) {
                if (std::chrono::duration<double>(std::chrono::high_resolution_clock::now() - info2->lastCollision).count() > info2->tics) {
                    info2->lastCollision = std::chrono::high_resolution_clock::now();
                    info2->onCollision(j, i);
                }
            }
        }
    }

    bool isColiding(std::vector<Hitbox::intRect> hitbox1, std::vector<Hitbox::intRect> hitbox2, Scale *s1, Scale *s2, Position *pos1, Position *pos2)
    {
        for (auto rect1: hitbox1) {
            Hitbox::intRect tmp1 = {
                    static_cast<int>(rect1.x * s1->x + pos1->x),
                    static_cast<int>(rect1.y * s1->y + pos1->y),
                    static_cast<int>(rect1.width * s1->x),
                    static_cast<int>(rect1.height * s1->y)};
            if (tmp1.width < 0) {
                tmp1.width = -tmp1.width;
                tmp1.x -= tmp1.width;
            }
            if (tmp1.height < 0) {
                tmp1.height = -tmp1.height;
                tmp1.y -= tmp1.height;
            }

            for (auto rect2: hitbox2) {

                Hitbox::intRect tmp2 = {
                        static_cast<int>(rect2.x * s2->x + pos2->x),
                        static_cast<int>(rect2.y * s2->y + pos2->y),
                        static_cast<int>(rect2.width * s2->x),
                        static_cast<int>(rect2.height * s2->y)};
                if (tmp2.width < 0) {
                    tmp2.width = -tmp2.width;
                    tmp2.x -= tmp2.width;
                }
                if (tmp2.height < 0) {
                    tmp2.height = -tmp2.height;
                    tmp2.y -= tmp2.height;
                }
                if (tmp1.x + tmp1.width >= tmp2.x &&
                    tmp1.x <= tmp2.x + tmp2.width &&
                    tmp1.y + tmp1.height >= tmp2.y &&
                    tmp1.y <= tmp2.y + tmp2.height) {
                    return true;
                }
            }
        }
        return false;
    }

    void CollisionSystem(ComponentList *componentList, std::vector<info_inputs> *inputs)
    {
        for (int i = 0; i < componentList->getSize(); i++) {
            if (componentList->getComponent("Hide", i) != nullptr)
                continue;
            if (componentList->getComponent("Position", i) &&
                componentList->getComponent("Hitbox", i) &&
                componentList->getComponent("Scale", i)) {
                auto position1 = static_cast<Position *>(componentList->getComponent("Position", i));
                auto size1 = static_cast<Hitbox *>(componentList->getComponent("Hitbox", i));
                auto scale1 = static_cast<Scale *>(componentList->getComponent("Scale", i));
                for (int j = 0; j < componentList->getSize(); j++) {
                    if (i == j)
                        continue;
                    if (componentList->getComponent("Position", j) &&
                        componentList->getComponent("Hitbox", j) &&
                        componentList->getComponent("Scale", i)) {
                        auto position2 = static_cast<Position *>(componentList->getComponent("Position", j));
                        auto size2 = static_cast<Hitbox *>(componentList->getComponent("Hitbox", j));
                        auto scale2 = static_cast<Scale *>(componentList->getComponent("Scale", j));
                        if (position2 == nullptr || size2 == nullptr || scale2 == nullptr) {
                            return;
                        }
                        if (isColiding(size1->hitbox, size2->hitbox, scale1, scale2, position1, position2)) {
                            CollisionHandling(componentList, i, j);
                        }
                    }
                }
            }
        }
    }

    void DestroyEntity(ComponentList *componentList, std::vector<info_inputs> *inputs)
    {
        for (int i = 0; i < componentList->getSize(); i++) {
            if (componentList->getComponent("LifeTime", i) != nullptr) {
                auto lifeTime = static_cast<LifeTime *>(componentList->getComponent("LifeTime", i));
                lifeTime->tics++;
                if (lifeTime->tics >= lifeTime->lifeTime) {
                    lifeTime->callback(i);
                    componentList->removeEntity(i);
                }
            }
            if (componentList->getComponent("Destroy", i) != nullptr) {
                componentList->removeEntity(i);
            }
        }
    }
}// namespace Haze
