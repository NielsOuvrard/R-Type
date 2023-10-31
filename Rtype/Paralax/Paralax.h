//
// Created by erwan on 10/15/23.
//

#pragma once

#include "../protocol.h"
#include "Cooldown/Cooldown.h"
#include "Missile/Missile.h"
#include <componentData.hpp>
#include <data.h>
#include <haze-core.hpp>
#include <net_data_channel.h>

/**
 * @class Paralax
 *
 * @brief Represents a parallax background in the game.
 *
 * The `Paralax` class manages the parallax background in the game, which adds depth and visual interest
 * to the game's environment. It provides functions to build, update, and communicate the background
 * to clients through the network channel.
 */
class Paralax {
public:
    /**
     * @brief Constructs a Paralax object.
     *
     * @param engine The game engine.
     * @param channel The data channel for network communication.
     */
    Paralax(Haze::Engine &engine, network::data_channel<protocol::data> &channel);

    /**
     * @brief Builds the parallax background.
     *
     * This function constructs the parallax background, including the layers or entities that make up
     * the parallax effect.
     */
    void build();

    /**
     * @brief Updates the state of the parallax background.
     *
     * This function is responsible for updating the state of the parallax background, creating the
     * illusion of depth in the game's environment.
     */
    void update();

    /**
     * @brief Sends the parallax background data to clients.
     *
     * This function sends data about the parallax background to clients through the network channel.
     */
    void send();

    /**
     * @brief Sends an update for the parallax background.
     *
     * This function sends an update for the parallax background to clients through the network channel.
     */
    void sendUpdate();

private:
    Haze::Engine &_engine;
    Haze::Entity *_bg1;///< The first layer of the parallax background.
    Haze::Entity *_bg2;///< The second layer of the parallax background.
    network::data_channel<protocol::data> &_channel;
};
