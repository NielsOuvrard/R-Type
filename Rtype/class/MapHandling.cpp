//
// Created by Niels Ouvrard on 27/10/2023.
//

#include "MapHandling.h"

void fill_EnemyData(EnemyData &data, nlohmann::json jsonData)
{
    data.damage = 0;
    data.type = 0;
    data.life = 0;
    data.path_sprite = "";

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
}

MapHandling::MapHandling(Haze::Engine &engine,
                         network::data_channel<protocol::data> &channel,
                         std::vector<std::unique_ptr<Wall>> &walls,
                         std::vector<std::unique_ptr<Enemy>> &enemies)
    : _engine(engine), _channel(channel), _walls(walls), _enemies(enemies), _index_map(0)
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

                    new_enemy_type.path_json = filePath;
                    _enemies_type.push_back(new_enemy_type);
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

void MapHandling::createMap()
{
    // Load sprite data for the walls from "ground.json"
    std::ifstream groundFile("assets/AnimationJSON/ground.json");

    if (!groundFile.is_open()) {
        std::cerr << "Error: Could not open 'ground.json' for reading" << std::endl;
        return;
    }
    groundFile >> _hitboxWalls;
    groundFile.close();

    // Load map data from "map.json"
    std::ifstream mapFile("assets/AnimationJSON/map.json");
    nlohmann::json mapData;
    if (!mapFile.is_open()) {
        std::cerr << "Error: Could not open 'map.json' for reading" << std::endl;
        return;
    }
    mapFile >> mapData;
    mapFile.close();

    // Retrieve the array of tiles from the map data
    _mapTiles = mapData["map"];
    // Iterate through each tile in the map
    for (const auto &tile: _mapTiles) {
        if (_index_map - 1 > WINDOW_WIDTH / (UNIVERSAL_SCALE * 48)) {
            break;
        }
        // Create and position the top wall
        _walls.emplace_back(std::make_unique<Wall>(_engine, _channel, _hitboxWalls, (48 * UNIVERSAL_SCALE) * _index_map, 0, false));
        _walls.back()->build(tile["tile_top"]);

        // Create and position the bottom wall
        _walls.emplace_back(std::make_unique<Wall>(_engine, _channel, _hitboxWalls, (48 * UNIVERSAL_SCALE) * _index_map, WINDOW_HEIGHT, true));
        _walls.back()->build(tile["tile_bottom"]);

        // Print the tile index
        std::cout << "Tile " << _index_map << " created." << std::endl;
        _index_map++;
    }

    std::cout << "Map successfully created." << std::endl;
}

void MapHandling::update()
{
    if (_walls.front()->get_x_position() < -(48 * 3)) {// * tile = 3 * 48
        // destroy
        _walls.front()->destroy();
        _walls.erase(_walls.begin());
        _walls.front()->destroy();
        _walls.erase(_walls.begin());

        float pos_wall_back = _walls.back()->get_x_position();

        // * read "enemies" inside of map
        //        _enemies.
        std::cout << "\u001B[0;32mNEW ENEMY ?\u001B[0;0m\n";
        auto &enemies_tile = _mapTiles[_index_map]["enemies"];

        if (enemies_tile != nullptr) {
            for (auto &enemy_tile: enemies_tile) {
                std::cout << "\u001B[0;31mNEW ENEMY !\u001B[0;0m\n";
                int16_t type_enemy_found = enemy_tile["type"];
                _enemies.emplace_back(std::make_unique<Enemy>(_engine, _channel));
                _enemies.back()->build(_enemies_type.back(), enemy_tile);// TODO put the good type, with map
            }
        }

        // Create and position the top wall
        _walls.emplace_back(std::make_unique<Wall>(_engine, _channel, _hitboxWalls, pos_wall_back + (48 * UNIVERSAL_SCALE), 0, false));
        _walls.back()->build(_mapTiles[_index_map]["tile_top"]);
        // Create and position the bottom wall
        _walls.emplace_back(std::make_unique<Wall>(_engine, _channel, _hitboxWalls, pos_wall_back + (48 * UNIVERSAL_SCALE), WINDOW_HEIGHT, true));
        _walls.back()->build(_mapTiles[_index_map]["tile_bottom"]);
        _index_map++;
    }
}
