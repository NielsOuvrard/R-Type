//
// Created by Niels Ouvrard on 27/10/2023.
//

#include "MapHandling.h"

#define NBR_TILES_ON_SCREEN 6

MapHandling::MapHandling(Haze::Engine &engine,
                         network::data_channel<protocol::data> &channel,
                         std::vector<std::unique_ptr<Wall>> &walls,
                         std::vector<std::unique_ptr<Enemy>> &enemies)
    : _engine(engine), _channel(channel), _walls(walls), _enemies(enemies)
{
}

void MapHandling::update()
{
    if (_walls.front()->get_x_position() < -(48 * 3)) {// * tile = 3 * 48
        std::cout << "_walls.front()->destroy\n";
        // destroy
        _walls.front()->destroy();
        _walls.erase(_walls.begin());
        _walls.front()->destroy();
        _walls.erase(_walls.begin());

        float pos_wall_back = _walls.back()->get_x_position();


        // * read "enemies" inside of map
        // Create and position the top wall
        _walls.emplace_back(std::make_unique<Wall>(_engine, _channel, _hitboxWalls, pos_wall_back + (48 * 3), 0, false));
        _walls.back()->build(_mapTiles[_index_map]["tile_top"]);
        // Create and position the bottom wall
        _walls.emplace_back(std::make_unique<Wall>(_engine, _channel, _hitboxWalls, pos_wall_back + (48 * 3), 600, true));
        _walls.back()->build(_mapTiles[_index_map]["tile_bottom"]);
        _index_map++;

        std::cout << "\033[0;31m map i = " << _index_map << " and _walls are " << _walls.size() << "\033[0;0m" << std::endl;
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
        if (_index_map > NBR_TILES_ON_SCREEN) {
            break;
        }
        // Create and position the top wall
        _walls.emplace_back(std::make_unique<Wall>(_engine, _channel, _hitboxWalls, (48 * 3) * _index_map, 0, false));
        _walls.back()->build(tile["tile_top"]);

        // Create and position the bottom wall
        _walls.emplace_back(std::make_unique<Wall>(_engine, _channel, _hitboxWalls, (48 * 3) * _index_map, 600, true));
        _walls.back()->build(tile["tile_bottom"]);

        // Print the tile index
        std::cout << "Tile " << _index_map << " created." << std::endl;
        _index_map++;
    }

    std::cout << "Map successfully created." << std::endl;
}
