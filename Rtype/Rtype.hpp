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

#include "Player.h"
#include "data.h"
#include "json.hpp"
#include "net_data_channel.h"
#include "wall.hpp"
#include <Factory.hpp>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <haze-core.hpp>
#include <haze-graphics.hpp>// ? sure about this ?
#include <iostream>

class Rtype : public network::data_channel<protocol::data> {
public:
    Rtype(asio::io_context &context);
    ~Rtype();

public:
    void start();
    void stop();

    void onReceive(udp::endpoint from, network::datagram<protocol::data> content) override;
    void sendEverything(udp::endpoint &to);

    void checkInactiveClients();

    void createPlayer(Player &player);
    Player &findPlayer(const asio::ip::udp::endpoint &endpoint);
    uint32_t findPlayerIndex(const asio::ip::udp::endpoint &endpoint);

private:
    Haze::Engine _engine;

    std::vector<Haze::Entity *> _entities;
    std::array<Player, 4> _players;
    bool _running = false;
};
