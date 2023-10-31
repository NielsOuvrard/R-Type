//
// Created by Niels Ouvrard on 29/10/2023.
//


#pragma once

#include "../config.h"
#include "../protocol.h"
#include "BossData.h"
#include "Cooldown/Cooldown.h"
#include "MapHandling/MapHandling.h"
#include "Missile/Missile.h"
#include <componentData.hpp>
#include <data.h>
#include <haze-core.hpp>
#include <net_data_channel.h>

using namespace asio::ip;
using namespace std::chrono_literals;

class Boss {
public:
    Boss(Haze::Engine &engine, network::data_channel<protocol::data> &channel);

    void build(std::string path);

    void send();

    void shoot();

    void update();

    void stopVelocity();

public:
    BossData _data = {};

    Haze::Entity *_body = nullptr;
    Haze::Entity *_tummy = nullptr;
    std::vector<Haze::Entity *> _tail;
    bool _isDead = false;///< Indicates whether the enemy is dead.

    std::list<std::unique_ptr<Missile>> _missiles;///< List of missiles fired by the enemy.

private:
    Haze::Engine &_engine;                          ///< The game engine.
    network::data_channel<protocol::data> &_channel;///< The network data channel.
    Cooldown _missileCd{5000ms};                    ///< Cooldown timer for missile firing.
};