//
// Created by Niels Ouvrard on 16/10/2023.
//

#pragma once

#include "../config.h"
#include "../protocol.h"
#include "Cooldown/Cooldown.h"
#include "ExplosionData.h"
#include "GameStructures.h"
#include <componentData.hpp>
#include <data.h>
#include <haze-core.hpp>
#include <net_data_channel.h>

using namespace std::chrono_literals;

/**
 * @brief Represents an explosion in the game.
 */
class Explosion {
public:
    /**
     * @brief Construct an Explosion object.
     *
     * @param engine The game engine.
     * @param channel The network data channel.
     * @param x The x-coordinate of the explosion.
     * @param y The y-coordinate of the explosion.
     */
    Explosion(DataGame dataGame, TypeEntities typeEntities, float x, float y, uint16_t type);

    /**
     * @brief Build the explosion entity with initial properties.
     */
    void build();

    /**
     * @brief Send the explosion entity to clients.
     */
    void send();

    /**
     * @brief Destroy the explosion entity.
     */
    void destroy();

    Haze::Entity *_entity = nullptr;///< The explosion entity.
    Cooldown _time_to_destroyCd{2s};///< Cooldown timer for destruction.

private:
    DataGame _dataGame;
    TypeEntities _typeEntities;

    float _x;///< The x-coordinate of the explosion.
    float _y;///< The y-coordinate of the explosion.
    uint16_t _type;
};
