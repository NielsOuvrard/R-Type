//
// Created by erwan on 10/15/23.
//

#pragma once

#include "../protocol.h"
#include <componentData.hpp>
#include <data.h>
#include <haze-core.hpp>
#include <net_data_channel.h>

/**
 * @class Missile
 *
 * @brief Represents a missile in the game.
 *
 * The `Missile` class is responsible for managing missile objects in the game. Missiles can be constructed,
 * positioned, and sent through the network to interact with other game entities.
 */
class Missile {
public:
    /**
     * @brief Constructs a Missile object.
     *
     * @param engine The game engine.
     * @param channel The data channel for network communication.
     * @param fromPlayer Indicates whether the missile was fired by a player.
     */
    Missile(Haze::Engine &engine, network::data_channel<protocol::data> &channel, bool fromPlayer);

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
    bool _fromPlayer;///< Indicates whether the missile was fired by a player.
    Haze::Engine &_engine;
    network::data_channel<protocol::data> &_channel;
};