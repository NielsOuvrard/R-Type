//
// Created by erwan on 10/15/23.
//

#pragma once

#include "../config.h"
#include "../protocol.h"
#include "Cooldown/Cooldown.h"
#include "GameStructures.h"
#include "Shot/Shot.h"
#include <componentData.hpp>
#include <data.h>
#include <haze-core.hpp>
#include <net_data_channel.h>

using namespace asio::ip;
using namespace std::chrono_literals;

/**
 * @class Player
 *
 * @brief Represents a player in the game.
 *
 * The `Player` class manages player objects in the game. Players can be constructed, updated, and
 * communicate with other players through the network channel. Each player has a unique identifier,
 * a score, health points (hp), and a set of missiles.
 */
class Player {
public:
    /**
     * @struct Remote
     *
     * @brief Represents a remote player's information.
     */
    struct Remote {
        asio::ip::udp::endpoint endpoint;///< The network endpoint for the remote player.
        Cooldown activityCd{10s};        ///< The cooldown for remote player activity.

        /**
         * @brief Constructs a Remote player object.
         *
         * @param endpoint The network endpoint of the remote player.
         */
        explicit Remote(udp::endpoint endpoint) : endpoint(std::move(endpoint)) { activityCd.Activate(); }
    };

    /**
     * @brief Constructs a Player object.
     *
     * @param engine The game engine.
     * @param channel The data channel for network communication.
     * @param id The unique identifier for the player.
     */
    Player(DataGame _dataGame, TypeEntities _typeEntities, uint32_t id);

    /**
     * @brief Builds the player object.
     *
     * This function constructs the player object.
     */
    void build();

    /**
     * @brief Updates the player's state.
     *
     * This function is responsible for updating the player's state during gameplay.
     */
    void update();

    /**
     * @brief Sends player data to clients.
     *
     * This function sends player data to clients using the network channel.
     */
    void send();

    /**
     * @brief Sends an update for the player.
     *
     * This function sends an update for the player object to clients.
     */
    void sendUpdate();

public:
    std::unique_ptr<Remote> _remote = nullptr;///< Information about the remote player.

    Haze::Entity *_entity = nullptr;///< The entity associated with the player.

    uint32_t _id = 0;   ///< The unique identifier of the player.
    uint32_t _score = 0;///< The player's score.
    int32_t _hp = 50;   ///< The player's health points.

    std::list<std::unique_ptr<Shot>> _missiles;///< The list of missiles fired by the player.
    Cooldown _missileCd{300ms};                ///< Cooldown for missile firing.

private:
    DataGame _dataGame;
    TypeEntities _typeEntities;
};
