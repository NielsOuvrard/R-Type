//
// Created by Niels Ouvrard on 29/10/2023.
//


#pragma once

#include "../config.h"
#include "../protocol.h"
#include "BossData.h"
#include "Cooldown/Cooldown.h"
#include "Map/Map.h"
#include "Shot/Shot.h"
#include <componentData.hpp>
#include <data.h>
#include <haze-core.hpp>
#include <net_data_channel.h>

using namespace asio::ip;
using namespace std::chrono_literals;

class Boss {
public:
    Boss(DataGame dataGame, TypeEntities typeEntities, nlohmann::json boss);

    void build(std::string path);

    void send();

    void shot();

    void update();

    void stopVelocity();

public:
    BossData _data = {};

    Haze::Entity *_body = nullptr;
    Haze::Entity *_tummy = nullptr;
    std::vector<Haze::Entity *> _tail;
    bool _isDead = false;///< Indicates whether the enemy is dead.

    std::list<std::unique_ptr<Shot>> _missiles;///< List of missiles fired by the enemy.

private:
    DataGame _dataGame;
    TypeEntities _typeEntities;

    uint16_t _y_next_shot;
    bool _next_shot_upper;
    uint16_t _type;
    Cooldown _missileCd{5ms};///< Cooldown timer for missile firing.
};