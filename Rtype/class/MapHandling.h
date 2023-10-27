//
// Created by Niels Ouvrard on 27/10/2023.
//

#pragma once

#include "../../Haze/inc/json.hpp"
#include "Enemy.h"
#include "Wall.hpp"
#include <Factory.hpp>
#include <haze-core.hpp>
#include <haze-graphics.hpp>
#include <net_data_channel.h>
#include <protocol.h>

// list of walls, enemies...

class MapHandling {
public:
    MapHandling(Haze::Engine &engine,
                network::data_channel<protocol::data> &channel,
                std::vector<std::unique_ptr<Wall>> &walls,
                std::vector<std::unique_ptr<Enemy>> &enemies);
    void update();
    void createMap();

private:
    Haze::Engine &_engine;
    network::data_channel<protocol::data> &_channel;
    std::vector<std::unique_ptr<Enemy>> &_enemies;


    Haze::Entity *_entity = nullptr;
    nlohmann::json _dataJSON;
    std::vector<std::unique_ptr<Wall>> &_walls;

    // * walls
    nlohmann::json _mapTiles;
    nlohmann::json _hitboxWalls;
    uint16_t _index_map;
};
