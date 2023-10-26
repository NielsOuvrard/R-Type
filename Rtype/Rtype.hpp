/*
** ooooooooo.           ooooooooooooo
** `888   `Y88.         8'   888   `8
**  888   .d88'              888      oooo    ooo oo.ooooo.   .ooooo.
**  888ooo88P'               888       `88.  .8'   888' `88b d88' `88b
**  888`88b.    8888888      888        `88..8'    888   888 888ooo888
**  888  `88b.               888         `888'     888   888 888    .o
** o888o  o888o             o888o         .8'      888bod8P' `Y8bod8P'
**                                    .o..P'       888
**                                    `Y8P'       o888o
**
** Rtype
*/

#pragma once
#include "../Client/json.hpp"
#include "Enemy.h"
#include "Explosion.h"
#include "Paralax.h"
#include "Player.h"
#include "Wall.hpp"
#include "data.h"
#include "net_data_channel.h"
#include "net_server.h"
#include "protocol.h"
#include <Factory.hpp>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <haze-core.hpp>
#include <haze-graphics.hpp>// ? sure about this ?
#include <iostream>

class Rtype {
public:
    Rtype(asio::io_context &context);
    ~Rtype();

public:
    void start();
    void stop();
    void update();
    void sendUpdate();

    void onReceive(udp::endpoint from, network::datagram<protocol::data> content);
    void sendEverything(udp::endpoint &to);
    [[nodiscard]] asio::ip::udp::endpoint getEndpoint() const;

    void updateMap();// TODO : map who generate itself and destroy itself
    void createMap();
    void checkInactiveClients();

    uint32_t getPlayerID(const asio::ip::udp::endpoint &endpoint);

private:
    Haze::Engine _engine;
    network::data_channel<protocol::data> _channel;

    Cooldown _enemySpawnCD{5s};

    // * walls
    nlohmann::json _mapTiles;
    nlohmann::json _hitboxWalls;
    uint16_t _index_map;

    std::unique_ptr<Paralax> _background;
    std::vector<std::unique_ptr<Wall>> _walls;
    std::vector<Haze::Entity *> _entities;
    std::vector<std::unique_ptr<Player>> _players;
    std::vector<std::unique_ptr<Explosion>> _explosions;
    std::vector<std::unique_ptr<Enemy>> _enemies;
    bool _running = false;
};
