//
// Created by erwan on 10/15/23.
//

#pragma once

#include "../protocol.h"
#include "Cooldown.h"
#include <componentData.hpp>
#include <data.h>
#include <haze-core.hpp>
#include <net_data_channel.h>


using namespace asio::ip;
using namespace std::chrono_literals;

class Player {
public:
    struct Remote {
        asio::ip::udp::endpoint endpoint;
        Cooldown activityCd{10s};

        explicit Remote(udp::endpoint endpoint) : endpoint(std::move(endpoint)) { activityCd.Activate(); }
    };

    Player(Haze::Engine &engine, network::data_channel<protocol::data> &channel, uint32_t id);
    void build();
    void update();
    void send();
    void changeScore();
    void sendUpdate();

public:
    std::unique_ptr<Remote> _remote = nullptr;
    Haze::Entity *_entity = nullptr;
    Haze::Entity *_scoreEntity = nullptr;

    uint32_t _id = 0;
    uint32_t _score = 0;
    // std::unique_ptr<element::TextInput> _scoreText;

private:
    Haze::Engine &_engine;
    network::data_channel<protocol::data> &_channel;
};
