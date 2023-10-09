/*
** EPITECH PROJECT, 2023
** cpp r-type
** File description:
** Rtype.hpp
*/

#pragma once

#include <haze-core.hpp>
#include <haze-graphics.hpp>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include "json.hpp"
#include "wall.hpp"
#include "data.h"
#include "net_data_channel.h"
// #include "GraphicClient.hpp"
// #include "Component.hpp"

class Rtype
{
private:
    Haze::Engine engine;
    Haze::Entity *entityVortex;
    Haze::Entity *entitySpaceship;
    Haze::Entity *entityShot;
    // srd::vector<Haze::Entity *> entityShots;
    Haze::Entity *entityWindow;
    Haze::Entity *entityWallTop;
    Haze::Entity *entityEnnemy;
    std::shared_ptr<network::data_channel<protocol::UDPProtocol>> _dataChannel;
    wall *wall1;
    wall *wall2;
    wall *wall3;
    wall *wall4;
    wall *wall5;
    wall *wall6;
    // Haze::Entity *entityBackground;
    Haze::Sprite *wallSprite = new Haze::Sprite("assets/wall.png");
    nlohmann::json jsonData;
    nlohmann::json sheet;
    sf::Event event;
    char isMoving = '\0';
    void keyPress();
    void keyRelease();
    void moveBackground();

public:
    Rtype();
    ~Rtype();
    void run(std::shared_ptr<network::data_channel<protocol::UDPProtocol>> _dataChannel);
    void moveUp(void *component);
    void moveDown(void *component);
    void moveLeft(void *component);
    void moveRight(void *component);
};
