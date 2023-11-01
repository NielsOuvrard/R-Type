//
// Created by erwan on 10/15/23.
//

#pragma once

#include "../config.h"
#include "../protocol.h"
#include "GameStructures.h"
#include "ShotData.h"
#include <componentData.hpp>
#include <data.h>
#include <haze-core.hpp>
#include <net_data_channel.h>

/**
 * @class Shot
 *
 * @brief Represents a missile in the game.
 *
 * The `Shot` class is responsible for managing missile objects in the game. Shots can be constructed,
 * positioned, and sent through the network to interact with other game entities.
 */
class Shot {
public:
    /**
     * @brief Constructs a Shot object.
     *
     * @param engine The game engine.
     * @param channel The data channel for network communication.
     * @param fromPlayer Indicates whether the missile was fired by a player.
     */
    Shot(Haze::Engine &engine, network::data_channel<protocol::data> &channel, bool fromPlayer, uint16_t type, TypeEntities typeEntities);

    /**
     * @brief Builds the missile at a specified position.
     *
     * @param x The X-coordinate of the missile's position.
     * @param y The Y-coordinate of the missile's position.
     */
    void build(float x, float y);

    /**
     * @brief Sends information about the missile to clients.
     *
     * This function sends information about the missile to clients through the network channel.
     */
    void send();

    Haze::Entity *_entity = nullptr;///< The entity associated with the missile.
    float _x;                       ///< The X-coordinate of the missile's position.
    float _y;                       ///< The Y-coordinate of the missile's position.

private:
    uint16_t _type;
    TypeEntities _typeEntities;

    bool _fromPlayer;///< Indicates whether the missile was fired by a player.
    Haze::Engine &_engine;
    network::data_channel<protocol::data> &_channel;
};
