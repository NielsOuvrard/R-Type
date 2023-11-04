//
// Created by Niels Ouvrard on 31/10/2023.
//

#pragma once

class Boss;
class Enemy;
class Explosion;
class Parallax;
class Player;
class Shot;
class Wall;

#include "Boss/BossData.h"
#include "Enemy/EnemyData.h"
#include "Explosion/ExplosionData.h"
#include "Shot/ShotData.h"

#include <cstdlib>
#include <map>
#include <net_data_channel.h>
#include <protocol.h>

typedef struct typeEntities {
    std::map<uint16_t, EnemyData> &enemies;
    std::map<uint16_t, ExplosionData> &explosions;
    std::map<uint16_t, ShotData> &shots;
    std::map<uint16_t, BossData> &bosses;
} TypeEntities;

typedef struct dataGame {
    Haze::Engine &engine;
    network::data_channel<protocol::data> &channel;
    // One by game
    std::unique_ptr<Parallax> &parallax;
    std::unique_ptr<Boss> &boss;
    // Several by game
    std::vector<std::unique_ptr<Shot>> &shots;// never used
    std::vector<std::unique_ptr<Wall>> &walls;
    std::vector<std::unique_ptr<Player>> &players;
    std::vector<std::unique_ptr<Explosion>> &explosions;
    std::vector<std::unique_ptr<Enemy>> &enemies;
    bool &map_moving;
} DataGame;
