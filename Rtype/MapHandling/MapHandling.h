//
// Created by Niels Ouvrard on 27/10/2023.
//

#pragma once

#include "../../Haze/inc/json.hpp"
#include "../config.h"
#include "Boss/Boss.h"
#include "Enemy/Enemy.h"
#include "Wall/Wall.h"
#include <Factory.hpp>
#include <haze-core.hpp>
#include <haze-graphics.hpp>
#include <net_data_channel.h>
#include <protocol.h>
// list of walls, enemies...
class Enemy;
class Boss;

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
                std::vector<std::unique_ptr<Enemy>> &enemies,
                std::unique_ptr<Boss> &bosses);

    /**
     * @brief Updates the game's map state.
     *
     * This function is responsible for updating the game's map. Create or not walls and enemies.
     */
    void update();

    /**
     * @brief Builds the game, ennemies and the map.
     *
     * This function builds the game.
     * In this order : createEnemies() ; loadMaps() ; createMap()
     */
    void build();

private:
    /**
     * @brief Creates enemy entity from a path.
     *
     * This function creates enemy entity according to their types.
     */
    void createEnemy(std::ifstream &fileStream, const std::string &filePath);

    /**
     * @brief Loads all maps paths in vector.
     *
     * Loading all maps paths inside a vector<string>.
     */
    void loadMaps();

    /**
     * @brief Creates the initial map layout.
     *
     * This function creates the initial map layout, including walls and other map elements.
     * Should be call each times a new map is load.
     * Open the map from the vector<string> created by loadMaps().
     */
    void createMap();

private:
    Haze::Engine &_engine;
    network::data_channel<protocol::data> &_channel;
    std::vector<std::unique_ptr<Enemy>> &_enemies;
    std::unique_ptr<Boss> &_boss;

    Haze::Entity *_entity = nullptr;
    nlohmann::json _dataJSON;
    std::vector<std::unique_ptr<Wall>> &_walls;
    std::vector<std::string> _maps_paths;

    std::map<uint16_t, EnemyData> _enemies_type;

    nlohmann::json _mapTiles;   ///< JSON data for map tiles.
    nlohmann::json _hitboxWalls;///< JSON data for hitbox walls.
    uint16_t _index_map;        ///< Index of the map layout.
    uint16_t _id_map;           ///< Index of the map layout.
};

using ActionFunction = std::function<void(std::ifstream &, const std::string &)>;
void processJsonFilesInDirectory(const std::string &directoryPath, const ActionFunction &action);