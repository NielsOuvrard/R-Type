//
// Created by erwan on 10/15/23.
//

#pragma once

#include "../config.h"
#include "../protocol.h"
#include "Cooldown/Cooldown.h"
#include "EnemyData.h"
#include "GameStructures.h"
#include "Map/Map.h"
#include "Shot/Shot.h"
#include <componentData.hpp>
#include <data.h>
#include <haze-core.hpp>
#include <net_data_channel.h>
#include <utility>


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
    Enemy(DataGame dataGame, TypeEntities typeEntities);

    /**
     * @brief Build the enemy entity with initial properties.
     */
    void build(EnemyData data, nlohmann::json mapData);

    /**
     * @brief Send the enemy entity to clients.
     */
    void send();

    /**
     * @brief Make the enemy shot a missile.
     */
    void shot();

    /**
     * @brief Update the enemy's state.
     */
    void update();

    void stopVelocity();

public:
    EnemyData _data = {};

    Haze::Entity *_entity = nullptr;///< The enemy entity.
    bool _isDead = false;           ///< Indicates whether the enemy is dead.

    // ? other way maybe ?
    std::list<std::unique_ptr<Shot>> _missiles;///< List of missiles fired by the enemy.

private:
    DataGame _dataGame;
    TypeEntities _typeEntities;

    Cooldown _missileCd{5000ms};///< Cooldown timer for missile firing.
};
