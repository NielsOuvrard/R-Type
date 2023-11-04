//
// Created by Niels Ouvrard on 27/10/2023.
//

#include "Map.h"

Map::Map(DataGame dataGame, TypeEntities typeEntities)
    : _dataGame(dataGame), _typeEntities(typeEntities), _index_map(0), _id_map(0)
{
    _walls_file_path = "";
    _parallax_path = "";
}

void Map::build()
{
    loadMaps();
    createMap();
}

void Map::loadMaps()
{
    const std::string directoryPath = "assets/json_files/maps";

    for (const auto &entry: std::filesystem::directory_iterator(directoryPath)) {
        if (entry.is_regular_file() && entry.path().extension() == ".json") {
            std::string filePath = entry.path().string();
            _maps_paths.push_back(filePath);
        }
    }
}

void Map::createMap()
{
    _id_map = 1;

    bool map_filled = false;
    while (!map_filled) {
        if (_id_map >= _maps_paths.size())
            _id_map = 0;
        std::ifstream fileStream(_maps_paths[_id_map]);
        if (fileStream.is_open()) {
            try {
                std::cout << "begin parsing file: " << _maps_paths[_id_map] << std::endl;
                nlohmann::json jsonData;
                fileStream >> jsonData;
                _mapTiles = jsonData["map"];
                _walls_file_path = jsonData["walls"];
                _parallax_path = jsonData["parallax"];
                map_filled = true;
            } catch (nlohmann::json::parse_error &e) {
                std::cerr << "Error parsing JSON file: " << _maps_paths[_id_map] << std::endl;
                std::cerr << e.what() << std::endl;
                _id_map++;
            }
            fileStream.close();
        } else {
            std::cerr << "Failed to open file: " << _maps_paths[_id_map] << std::endl;
            _id_map++;
        }
    }
    _dataGame.parallax->build(_parallax_path);

    std::ifstream wallsFileStream(_walls_file_path);
    if (wallsFileStream.is_open()) {
        try {
            std::cout << "begin parsing file: " << _maps_paths[_id_map] << std::endl;
            nlohmann::json jsonData;
            wallsFileStream >> _hitboxWalls;

        } catch (nlohmann::json::parse_error &e) {
            std::cerr << "Error parsing JSON file: " << _maps_paths[_id_map] << std::endl;
            std::cerr << e.what() << std::endl;
            _id_map++;
        }
        wallsFileStream.close();
    } else {
        std::cerr << "Failed to open file: " << _maps_paths[_id_map] << std::endl;
        _id_map++;
    }


    // Iterate through each tile in the map
    for (const auto &tile: _mapTiles) {
        if (_index_map - 2 > WINDOW_WIDTH / (UNIVERSAL_SCALE * SIZE_TILE)) {
            break;
        }

        // Create and position the top wall
        try {
            _dataGame.walls.emplace_back(std::make_unique<Wall>(_dataGame, _hitboxWalls, (SIZE_TILE * UNIVERSAL_SCALE) * _index_map, 0, false, _walls_file_path));
            _dataGame.walls.back()->build(tile["tile_top"]);
        } catch (nlohmann::json::parse_error &e) {
            std::cerr << "Error parsing JSON file: " << _maps_paths[_id_map] << std::endl;
            std::cerr << e.what() << std::endl;
        }

        // Create and position the bottom wall
        try {
            _dataGame.walls.emplace_back(std::make_unique<Wall>(_dataGame, _hitboxWalls, (SIZE_TILE * UNIVERSAL_SCALE) * _index_map, WINDOW_HEIGHT, true, _walls_file_path));
            _dataGame.walls.back()->build(tile["tile_bottom"]);
        } catch (nlohmann::json::parse_error &e) {
            std::cerr << "Error parsing JSON file: " << _maps_paths[_id_map] << std::endl;
            std::cerr << e.what() << std::endl;
        }
        _index_map++;
    }
}

void Map::update()
{
    _dataGame.parallax->update();
    if (_dataGame.walls.front()->get_x_position() < -(SIZE_TILE * UNIVERSAL_SCALE * 2)) {// * tile = 3 * SIZE_TILE
        // destroy
        _dataGame.walls.front()->destroy();
        _dataGame.walls.erase(_dataGame.walls.begin());
        _dataGame.walls.front()->destroy();
        _dataGame.walls.erase(_dataGame.walls.begin());

        float pos_wall_back = _dataGame.walls.back()->get_x_position();

        if (_index_map >= _mapTiles.size()) {
            // * stop scrolling the map
            for (auto &wall: _dataGame.walls) {
                wall->stopVelocity();
            }
            for (auto &enemy: _dataGame.enemies) {
                enemy->stopVelocity();
            }
            if (_dataGame.boss) {
                _dataGame.boss->stopVelocity();
            }
            for (auto &shot: _dataGame.shots) {
                shot->stopVelocity();
            }
            _dataGame.map_moving = false;
            return;
        }

        // * read "enemies" inside of map
        auto &enemies_tile = _mapTiles[_index_map]["enemies"];

        if (enemies_tile != nullptr) {
            for (auto &enemy_tile: enemies_tile) {
                // * create enemy
                try {
                    _dataGame.enemies.emplace_back(std::make_unique<Enemy>(_dataGame, _typeEntities));
                    _dataGame.enemies.back()->build(_typeEntities.enemies[enemy_tile["type"]], enemy_tile);
                } catch (nlohmann::json::parse_error &e) {
                    std::cerr << "Error parsing JSON file: " << _maps_paths[_id_map] << std::endl;
                    std::cerr << e.what() << std::endl;
                }
            }
        }

        if (_mapTiles[_index_map].contains("boss")) {
            nlohmann::json boss = _mapTiles[_index_map]["boss"];
            try {
                _dataGame.boss = std::make_unique<Boss>(_dataGame, _typeEntities, boss);
                _dataGame.boss->build("assets/json_files/bosses/dobkeratops.json");// TODO boss ID
            } catch (nlohmann::json::parse_error &e) {
                std::cerr << "Error parsing JSON file: " << _maps_paths[_id_map] << std::endl;
                std::cerr << e.what() << std::endl;
            }
        }


        // Create and position the top wall
        try {
            _dataGame.walls.emplace_back(std::make_unique<Wall>(_dataGame, _hitboxWalls, pos_wall_back + (SIZE_TILE * UNIVERSAL_SCALE), 0, false, _walls_file_path));
            _dataGame.walls.back()->build(_mapTiles[_index_map]["tile_top"]);
        } catch (nlohmann::json::parse_error &e) {
            std::cerr << "Error parsing JSON file: " << _maps_paths[_id_map] << std::endl;
            std::cerr << e.what() << std::endl;
        }

        // Create and position the bottom wall
        try {
            _dataGame.walls.emplace_back(std::make_unique<Wall>(_dataGame, _hitboxWalls, pos_wall_back + (SIZE_TILE * UNIVERSAL_SCALE), WINDOW_HEIGHT, true, _walls_file_path));
            _dataGame.walls.back()->build(_mapTiles[_index_map]["tile_bottom"]);
        } catch (nlohmann::json::parse_error &e) {
            std::cerr << "Error parsing JSON file: " << _maps_paths[_id_map] << std::endl;
            std::cerr << e.what() << std::endl;
        }
        _index_map++;
    }
}
