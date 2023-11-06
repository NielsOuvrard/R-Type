/*
** EPITECH PROJECT, 2023
** cpp r-type
** File description:
** Cocs-game.hpp
*/

#pragma once

#include "data.h"
#include "net_data_channel.h"
#include "net_server.h"
#include "protocol.h"
#include "Player.h"
#include "Ball.h"
#include "Cooldown.h"
#include <cstdlib>
#include <ctime>
#include <fstream>

class Cocs_game
{
public:
    Cocs_game(asio::io_context &context);
    ~Cocs_game();

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

    bool _running;
    std::vector<Haze::Entity *> _entities;
    std::vector<std::unique_ptr<Player>> _players;
    std::unique_ptr<Player> player;
    std::unique_ptr<Ball> _ball;
};

