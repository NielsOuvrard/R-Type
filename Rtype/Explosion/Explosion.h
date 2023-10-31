//
// Created by Niels Ouvrard on 16/10/2023.
//

#pragma once

#include "../config.h"
#include "../protocol.h"
#include "Cooldown/Cooldown.h"
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
    Explosion(Haze::Engine &engine, network::data_channel<protocol::data> &channel, float x, float y);

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
    //    Haze::SfAudio &_sound;
    Haze::Engine &_engine;                          ///< The game engine.
    network::data_channel<protocol::data> &_channel;///< The network data channel.
    float _x;                                       ///< The x-coordinate of the explosion.
    float _y;                                       ///< The y-coordinate of the explosion.
};
