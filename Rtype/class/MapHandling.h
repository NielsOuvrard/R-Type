//
// Created by Niels Ouvrard on 27/10/2023.
//

#pragma once

#include "../../Haze/inc/json.hpp"
#include "../config.h"
#include "Enemy.h"
#include "EnemyData.h"
#include "Wall.h"
#include <Factory.hpp>
#include <haze-core.hpp>
#include <haze-graphics.hpp>
#include <net_data_channel.h>
#include <protocol.h>
// list of walls, enemies...
class Enemy;

/**
 * @class MapHandling
 *
 * @brief Handles map-related operations in the game.
 *
 * The `MapHandling` class is responsible for managing and updating the game's map, including walls and enemies.
 * It provides functions for updating the map and creating the map layout.
 */
class MapHandling {
public:
    /**
     * @brief Constructs a MapHandling object.
     *
     * @param engine The game engine.
     * @param channel The data channel for network communication.
     * @param walls A vector of unique pointers to wall objects.
     * @param enemies A vector of unique pointers to enemy objects.
     */
    MapHandling(Haze::Engine &engine,
                network::data_channel<protocol::data> &channel,
                std::vector<std::unique_ptr<Wall>> &walls,
                std::vector<std::unique_ptr<Enemy>> &enemies);

    /**
     * @brief Updates the game's map state.
     *
     * This function is responsible for updating the game's map, including the position of walls and enemies.
     */
    void update();

    /**
     * @brief Creates the initial map layout.
     *
     * This function creates the initial map layout, including walls and other map elements.
     */
    void createMap();

private:
    Haze::Engine &_engine;
    network::data_channel<protocol::data> &_channel;
    std::vector<std::unique_ptr<Enemy>> &_enemies;

    Haze::Entity *_entity = nullptr;
    nlohmann::json _dataJSON;
    std::vector<std::unique_ptr<Wall>> &_walls;

    std::map<uint16_t, EnemyData> _enemies_type;

    nlohmann::json _mapTiles;   ///< JSON data for map tiles.
    nlohmann::json _hitboxWalls;///< JSON data for hitbox walls.
    uint16_t _index_map;        ///< Index of the map layout.
};
