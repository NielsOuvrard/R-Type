//
// Created by erwan on 10/15/23.
//

#pragma once

#include "Cooldown.h"
#include "Entity.hpp"
#include "net_common.h"
#include <cstdint>
#include <iostream>
#include <memory>

using namespace asio::ip;
using namespace std::chrono_literals;

struct Player {

    struct Remote {
        asio::ip::udp::endpoint endpoint;
        Cooldown activityCd{10s};

        explicit Remote(udp::endpoint endpoint) : endpoint(std::move(endpoint)) { activityCd.Activate(); }
    };

    std::unique_ptr<Remote> remote = nullptr;
    Haze::Entity *entity = nullptr;

    uint32_t id = 0;
    uint32_t hp = 20;
    uint32_t score = 0;

    Cooldown missileCd{50ms};
};
