//
// Created by erwan on 10/15/23.
//

#pragma once

#include "../config.h"
#include "../protocol.h"
#include "Cooldown.h"
#include "EnemyData.h"
#include "MapHandling.h"
#include "Missile.h"
#include <componentData.hpp>
#include <data.h>
#include <haze-core.hpp>
#include <net_data_channel.h>

using namespace asio::ip;
using namespace std::chrono_literals;

/**
 * @brief Represents an enemy in the game.
 */
class Enemy {
public:
    /**
     * @brief Construct an Enemy object.
     *
     * @param engine The game engine.
     * @param channel The network data channel.
     */
    Enemy(Haze::Engine &engine, network::data_channel<protocol::data> &channel);

    /**
     * @brief Build the enemy entity with initial properties.
     */
    void build(EnemyData data, nlohmann::json mapData);

    /**
     * @brief Send the enemy entity to clients.
     */
    void send();

    /**
     * @brief Make the enemy shoot a missile.
     */
    void shoot();

    /**
     * @brief Update the enemy's state.
     */
    void update();

    void stopVelocity();

public:
    EnemyData _data = {};

    Haze::Entity *_entity = nullptr;///< The enemy entity.
    bool _isDead = false;           ///< Indicates whether the enemy is dead.

    std::list<std::unique_ptr<Missile>> _missiles;///< List of missiles fired by the enemy.

private:
    Haze::Engine &_engine;                          ///< The game engine.
    network::data_channel<protocol::data> &_channel;///< The network data channel.
    Cooldown _missileCd{5000ms};                    ///< Cooldown timer for missile firing.
};
