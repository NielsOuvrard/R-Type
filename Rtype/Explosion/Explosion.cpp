//
// Created by Niels Ouvrard on 16/10/2023.
//

#include "Explosion.h"

/**
 * @brief Construct an Explosion object.
 *
 * @param engine The game engine.
 * @param channel The network data channel.
 * @param x The x-coordinate of the explosion.
 * @param y The y-coordinate of the explosion.
 */
Explosion::Explosion(DataGame dataGame, TypeEntities typeEntities, float x, float y, uint16_t type)
    : _dataGame(dataGame), _typeEntities(typeEntities), _x(x), _y(y), _type(type)
{
}

/**
 * @brief Build the explosion entity with initial components.
 */
void Explosion::build()
{
    // Activate the time-to-destroy cooldown
    _time_to_destroyCd.Activate();

    // Create a new entity
    _entity = _dataGame.engine.createEntity();

    // Add Position, Velocity, and Scale components to the entity
    _entity->addComponent(new Haze::Position(_x, _y));
    _entity->addComponent(new Haze::Velocity(0, 0, 0.1));
    _entity->addComponent(new Haze::Scale(UNIVERSAL_SCALE, UNIVERSAL_SCALE));
}

/**
 * @brief Send messages to create and initialize the explosion entity.
 */
void Explosion::send()
{
    // Send messages to create the explosion entity
    _dataGame.channel.sendGroup(RType::message::createEntity(_entity->getId()));
    _dataGame.channel.sendGroup(RType::message::addComponent(_entity->getId(), "Audio", new Haze::AudioData{"assets/sounds/explosion.wav"}, sizeof(Haze::AudioData)));
    // Send messages to add Position, Scale, Sprite, and Animation components
    _dataGame.channel.sendGroup(RType::message::addComponent(_entity->getId(), "Position", new Haze::PositionData{_x, _y}, sizeof(Haze::PositionData)));
    _dataGame.channel.sendGroup(RType::message::addComponent(_entity->getId(), "Scale", new Haze::ScaleData{UNIVERSAL_SCALE, UNIVERSAL_SCALE}, sizeof(Haze::ScaleData)));

    auto elem_sprite = new Haze::SpriteData();
    strncpy(elem_sprite->path, _typeEntities.explosions[_type].path_sprite.c_str(), sizeof(elem_sprite->path));
    elem_sprite->path[sizeof(elem_sprite->path) - 1] = '\0';
    _dataGame.channel.sendGroup(RType::message::addComponent(_entity->getId(), "Sprite", elem_sprite, sizeof(Haze::SpriteData)));

    auto elem_animation = new Haze::AnimationData();
    strncpy(elem_animation->path, _typeEntities.explosions[_type].path_json.c_str(), sizeof(elem_animation->path));
    elem_animation->path[sizeof(elem_animation->path) - 1] = '\0';
    _dataGame.channel.sendGroup(RType::message::addComponent(_entity->getId(), "Animation", elem_animation, sizeof(Haze::AnimationData)));
}

/**
 * @brief Send a message to destroy the explosion entity.
 */
void Explosion::destroy()
{
    // Send a message to initiate the destruction of the explosion entity
    _dataGame.channel.sendGroup(RType::message::addComponent(_entity->getId(), "Destroy", nullptr, 0));

    // Add a Destroy component to the entity
    _entity->addComponent(new Haze::Destroy());

    // Set the entity to nullptr
    _entity = nullptr;
}
