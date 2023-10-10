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

#include "data.h"
#include "json.hpp"
#include "net_data_channel.h"
#include "wall.hpp"
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <haze-core.hpp>
#include <haze-graphics.hpp>
#include <iostream>

// Haze::Engine
#define VORTEX 0
#define SPACESHIP 1
#define SHOT 2
#define WINDOW 3
#define WALL_TOP 4
#define ENNEMY 5
#define BACKGROUND 6

class Rtype : public network::data_channel<protocol::data>
{
protected:
    Haze::Engine engine;

    std::vector<Haze::Entity *> entities;
    std::vector<wall *> walls;

    std::shared_ptr<network::data_channel<protocol::data>> _dataChannel;

    Haze::Sprite *wallSprite = new Haze::Sprite("assets/wall.png"); // ? sure about this ?

    nlohmann::json jsonData;
    nlohmann::json sheet;

    sf::Event event;

    char isMoving = '\0';
    void keyPress();
    void keyRelease();
    void moveBackground();

public:
    Rtype(asio::io_context &context);
    ~Rtype();
    void run(std::shared_ptr<network::data_channel<protocol::data>> _dataChannel);
    void moveUp(void *component);
    void moveDown(void *component);
    void moveLeft(void *component);
    void moveRight(void *component);
    // void onReceive(udp::endpoint from, datagram<T> content) override;
    void onReceive(udp::endpoint from, network::datagram<protocol::data> content) override;
};
