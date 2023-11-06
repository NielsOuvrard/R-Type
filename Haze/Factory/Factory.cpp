/*
** EPITECH PROJECT, 2023
** B-CPP-500-MAR-5-1-rtype-erwan.gonzales
** File description:
** Factory
*/

#include "Factory.hpp"

namespace Haze {
    Factory::Factory()
    {
    }

    Factory::~Factory()
    {
    }

    Component *Factory::createComponent(std::string type, std::array<uint8_t, 256> data)
    {
        if (type == "Position") {
            PositionData *position = reinterpret_cast<PositionData *>(data.data());
            return new Position(position->x, position->y);
        }
        if (type == "Scale") {
            ScaleData *scale = reinterpret_cast<ScaleData *>(data.data());
            return new Scale(scale->x, scale->y);
        }
        if (type == "Velocity") {
            VelocityData *velocity = reinterpret_cast<VelocityData *>(data.data());
            return new Velocity(velocity->x, velocity->y, velocity->time);
        }
        if (type == "SinVelocity") {
            SinVelocityData *sinVelocity = reinterpret_cast<SinVelocityData *>(data.data());
            return new SinVelocity(sinVelocity->x, sinVelocity->time, sinVelocity->amplitude, sinVelocity->frequency, sinVelocity->offset);
        }
        if (type == "CircleVelocity") {
            CircleVelocityData *circleVelocity = reinterpret_cast<CircleVelocityData *>(data.data());
            return new CircleVelocity(circleVelocity->x, circleVelocity->time, circleVelocity->radius, circleVelocity->offset);
        }
        if (type == "Move") {
            MoveData *move = reinterpret_cast<MoveData *>(data.data());
            return new Move(move->x, move->y);
        }
        if (type == "Interpolation") {
            InterpolationData *interpolation = reinterpret_cast<InterpolationData *>(data.data());
            return new Interpolation(interpolation->framerate);
        }
        if (type == "Health") {
            HealthData *health = reinterpret_cast<HealthData *>(data.data());
            return new Health(health->health);
        }
        if (type == "Damage") {
            DamageData *damage = reinterpret_cast<DamageData *>(data.data());
            return new Damage(damage->damage);
        }
        if (type == "Collision") {
            CollisionData *collision = reinterpret_cast<CollisionData *>(data.data());
            return new Collision(collision->scene, collision->behavior);
        }
        if (type == "Hitbox") {
            HitboxData *hitbox = reinterpret_cast<HitboxData *>(data.data());
            return new Hitbox({hitbox->hitbox});
        }
        if (type == "LifeTime") {
            LifeTimeData *lifeTime = reinterpret_cast<LifeTimeData *>(data.data());
            return new LifeTime(lifeTime->lifeTime, [](int id) {});
        }
        if (type == "BulletDrop") {
            BulletDropData *bulletDrop = reinterpret_cast<BulletDropData *>(data.data());
            return new BulletDrop(bulletDrop->strength, bulletDrop->angle, bulletDrop->time);
        }
#ifdef USE_SFML
        if (type == "Sprite") {
            SpriteData *sprite = reinterpret_cast<SpriteData *>(data.data());
            return new Sprite(sprite->path);
        }
        if (type == "Window") {
            WindowData *window = reinterpret_cast<WindowData *>(data.data());
            return new Window(window->width, window->height);
        }
        if (type == "Audio") {
            AudioData *audio = reinterpret_cast<AudioData *>(data.data());
            return new Audio(audio->path);
        }
        if (type == "Animation") {
            AnimationData *animation = reinterpret_cast<AnimationData *>(data.data());
            return new Animation(animation->path);
        }
        if (type == "SpriteCropped") {
            SpriteCroppedData *spriteCropped = reinterpret_cast<SpriteCroppedData *>(data.data());
            return new SpriteCropped(spriteCropped->id);
        }
        if (type == "HitboxDisplay") {
            return new HitboxDisplay;
        }
        if (type == "Text") {
            TextData *text = reinterpret_cast<TextData *>(data.data());
            return new Text(text->text, text->r, text->g, text->b, text->a, text->path);
        }
#endif
        return nullptr;
    }
}// namespace Haze
