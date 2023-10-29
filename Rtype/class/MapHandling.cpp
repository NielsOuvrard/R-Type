//
// Created by Niels Ouvrard on 27/10/2023.
//

#include "MapHandling.h"

void fill_EnemyData(EnemyData &data, nlohmann::json jsonData)
{
    data.damage = 0;
    data.type = 0;
    data.life = 1;
    data.path_sprite = "";
    data.hitBoxData = {};
    data.shot_type = -1;


    if (jsonData.contains("type")) {
        data.type = jsonData["type"];
    }
    if (jsonData.contains("damage")) {
        data.damage = jsonData["damage"];
    }
    if (jsonData.contains("life")) {
        data.life = jsonData["life"];
    }
    if (jsonData.contains("path_sprite")) {
        data.path_sprite = jsonData["path_sprite"];
    }
    if (jsonData.contains("hitbox")) {
        if (jsonData["hitbox"].contains("x"))
            data.hitBoxData.x = jsonData["hitbox"]["x"];
        if (jsonData["hitbox"].contains("y"))
            data.hitBoxData.y = jsonData["hitbox"]["y"];
        if (jsonData["hitbox"].contains("width"))
            data.hitBoxData.width = jsonData["hitbox"]["width"];
        if (jsonData["hitbox"].contains("height"))
            data.hitBoxData.height = jsonData["hitbox"]["height"];
    }
    if (jsonData.contains("shot_type")) {
        data.shot_type = jsonData["shot_type"];
    }
}

MapHandling::MapHandling(Haze::Engine &engine,
                         network::data_channel<protocol::data> &channel,
                         std::vector<std::unique_ptr<Wall>> &walls,
                         std::vector<std::unique_ptr<Enemy>> &enemies)
    : _engine(engine), _channel(channel), _walls(walls), _enemies(enemies), _index_map(0), _id_map(0)
{
}

// MapHandling::MapHandling(Haze::Engine &engine,
//                          network::data_channel<protocol::data> &channel,
//                          std::vector<std::unique_ptr<Wall>> &walls,
//                          std::vector<std::unique_ptr<Enemy>> &enemies,
//                          std::unique_ptr<Boss> &boss)
//     : _engine(engine), _channel(channel), _walls(walls), _enemies(enemies), _index_map(0), _id_map(0), _boss(boss)
// {
// }

void MapHandling::build()
{
    createEnemies();
    loadMaps();
    createMap();
}

void MapHandling::createEnemies()
{
    const std::string directoryPath = "assets/enemies";

    for (const auto &entry: std::filesystem::directory_iterator(directoryPath)) {
        if (entry.is_regular_file() && entry.path().extension() == ".json") {
            std::string filePath = entry.path().string();
            std::ifstream fileStream(filePath);

            if (fileStream.is_open()) {
                try {
                    std::cout << "begin parsing file: " << filePath << std::endl;

                    nlohmann::json jsonData;
                    fileStream >> jsonData;

                    EnemyData new_enemy_type;
                    fill_EnemyData(new_enemy_type, jsonData);
                    uint16_t type = jsonData["type"];

                    new_enemy_type.path_json = filePath;
                    _enemies_type[type] = (new_enemy_type);
                } catch (nlohmann::json::parse_error &e) {
                    std::cerr << "Error parsing JSON file: " << filePath << std::endl;
                    std::cerr << e.what() << std::endl;
                }

                fileStream.close();
            } else {
                std::cerr << "Failed to open file: " << filePath << std::endl;
            }
        }
    }
}

void MapHandling::loadMaps()
{
    // ? add a type of mapTiles, so we can have infinity of sprites and hitbox
    // Load sprite data for the walls from "ground.json"
    std::ifstream groundFile("assets/AnimationJSON/ground.json");

    if (!groundFile.is_open()) {
        std::cerr << "Error: Could not open 'ground.json' for reading" << std::endl;
        return;
    }
    groundFile >> _hitboxWalls;
    groundFile.close();

    const std::string directoryPath = "assets/maps";

    for (const auto &entry: std::filesystem::directory_iterator(directoryPath)) {
        if (entry.is_regular_file() && entry.path().extension() == ".json") {
            std::string filePath = entry.path().string();
            _maps_paths.push_back(filePath);
        }
    }
}

void MapHandling::createMap()
{
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
    // Iterate through each tile in the map
    for (const auto &tile: _mapTiles) {
        if (_index_map - 1 > WINDOW_WIDTH / (UNIVERSAL_SCALE * SIZE_TILE)) {
            break;
        }

        // Create and position the top wall
        try {
            _walls.emplace_back(std::make_unique<Wall>(_engine, _channel, _hitboxWalls, (SIZE_TILE * UNIVERSAL_SCALE) * _index_map, 0, false));
            _walls.back()->build(tile["tile_top"]);
        } catch (nlohmann::json::parse_error &e) {
            std::cerr << "Error parsing JSON file: " << _maps_paths[_id_map] << std::endl;
            std::cerr << e.what() << std::endl;
        }

        // Create and position the bottom wall
        try {
            _walls.emplace_back(std::make_unique<Wall>(_engine, _channel, _hitboxWalls, (SIZE_TILE * UNIVERSAL_SCALE) * _index_map, WINDOW_HEIGHT, true));
            _walls.back()->build(tile["tile_bottom"]);
        } catch (nlohmann::json::parse_error &e) {
            std::cerr << "Error parsing JSON file: " << _maps_paths[_id_map] << std::endl;
            std::cerr << e.what() << std::endl;
        }
        _index_map++;
    }
}

void MapHandling::update()
{
    if (_walls.front()->get_x_position() < -(SIZE_TILE * UNIVERSAL_SCALE)) {// * tile = 3 * SIZE_TILE
        // destroy
        _walls.front()->destroy();
        _walls.erase(_walls.begin());
        _walls.front()->destroy();
        _walls.erase(_walls.begin());

        float pos_wall_back = _walls.back()->get_x_position();

        if (_index_map >= _mapTiles.size()) {
            // * stop scrolling the map
            for (auto &wall: _walls) {
                wall->stopVelocity();
            }
            for (auto &enemy: _enemies) {
                enemy->stopVelocity();
            }
            return;
        }

        // * read "enemies" inside of map
        auto &enemies_tile = _mapTiles[_index_map]["enemies"];

        if (enemies_tile != nullptr) {
            for (auto &enemy_tile: enemies_tile) {
                // * create enemy
                try {
                    _enemies.emplace_back(std::make_unique<Enemy>(_engine, _channel));
                    _enemies.back()->build(_enemies_type[enemy_tile["type"]], enemy_tile);
                } catch (nlohmann::json::parse_error &e) {
                    std::cerr << "Error parsing JSON file: " << _maps_paths[_id_map] << std::endl;
                    std::cerr << e.what() << std::endl;
                }
            }
        }

        // Create and position the top wall
        try {
            _walls.emplace_back(std::make_unique<Wall>(_engine, _channel, _hitboxWalls, pos_wall_back + (SIZE_TILE * UNIVERSAL_SCALE), 0, false));
            _walls.back()->build(_mapTiles[_index_map]["tile_top"]);
        } catch (nlohmann::json::parse_error &e) {
            std::cerr << "Error parsing JSON file: " << _maps_paths[_id_map] << std::endl;
            std::cerr << e.what() << std::endl;
        }

        // Create and position the bottom wall
        try {
            _walls.emplace_back(std::make_unique<Wall>(_engine, _channel, _hitboxWalls, pos_wall_back + (SIZE_TILE * UNIVERSAL_SCALE), WINDOW_HEIGHT, true));
            _walls.back()->build(_mapTiles[_index_map]["tile_bottom"]);
        } catch (nlohmann::json::parse_error &e) {
            std::cerr << "Error parsing JSON file: " << _maps_paths[_id_map] << std::endl;
            std::cerr << e.what() << std::endl;
        }
        _index_map++;
    }
}
