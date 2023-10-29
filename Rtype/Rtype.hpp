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
#include "Boss.h"
#include "Enemy.h"
#include "Explosion.h"
#include "MapHandling.h"
#include "Paralax.h"
#include "Player.h"
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

/**
 * @class Rtype
 *
 * @brief Represents the main application class for the Rtype game.
 *
 * The `Rtype` class is responsible for managing the Rtype game, including handling game logic,
 * network communication, and rendering. It uses the Asio library for networking and other
 * components for game management.
 */
class Rtype {
public:
    /**
     * @brief Constructs an instance of the Rtype class.
     *
     * @param context The Asio io_context used for network communication.
     */
    Rtype(asio::io_context &context);

    /**
     * @brief Destroys an instance of the Rtype class.
     */
    ~Rtype();

public:
    /**
     * @brief Starts the Rtype game.
     *
     * This function initiates the game loop and begins running the Rtype game.
     */
    void start();

    /**
     * @brief Stops the Rtype game.
     *
     * This function stops the game loop and terminates the Rtype game.
     */
    void stop();

    /**
     * @brief Updates the game state.
     *
     * This function is responsible for updating the game's state, including entities, collisions, and more.
     */
    void update();

    /**
     * @brief Sends updates to connected clients.
     *
     * This function sends game updates to all connected clients.
     */
    void sendUpdate();

    /**
     * @brief Callback function for handling received datagrams.
     *
     * @param from The endpoint from which the datagram was received.
     * @param content The received data content.
     */
    void onReceive(udp::endpoint from, network::datagram<protocol::data> content);

    /**
     * @brief Sends game data to a specific endpoint.
     *
     * @param to The endpoint to which the game data should be sent.
     */
    void sendEverything(udp::endpoint &to);

    /**
     * @brief Retrieves the local endpoint of the Rtype instance.
     *
     * @return The local endpoint.
     */
    [[nodiscard]] asio::ip::udp::endpoint getEndpoint() const;

    /**
     * @brief Checks for inactive clients and performs necessary actions.
     */
    void checkInactiveClients();

    /**
     * @brief Retrieves the player ID associated with a specific endpoint.
     *
     * @param endpoint The endpoint of the player.
     * @return The player's ID.
     */
    uint32_t getPlayerID(const asio::ip::udp::endpoint &endpoint);

private:
    Haze::Engine _engine;
    network::data_channel<protocol::data> _channel;

    Cooldown _enemySpawnCD{5s};

    std::unique_ptr<MapHandling> _mapHandler;
    std::unique_ptr<Paralax> _background;
    std::vector<std::unique_ptr<Wall>> _walls;
    std::vector<Haze::Entity *> _entities;
    std::vector<std::unique_ptr<Player>> _players;
    std::vector<std::unique_ptr<Explosion>> _explosions;
    std::vector<std::unique_ptr<Enemy>> _enemies;
    std::unique_ptr<Boss> _boss;
    bool _running = false;
};
