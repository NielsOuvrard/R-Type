/*
** EPITECH PROJECT, 2023
** cpp r-type
** File description:
** ball.h
*/

#pragma once

#include "../protocol.h"
#include <componentData.hpp>
#include <data.h>
#include <haze-core.hpp>
#include <net_data_channel.h>

using namespace asio::ip;
using namespace std::chrono_literals;

class Ball {
    public:
        Ball(Haze::Engine &engine, network::data_channel<protocol::data> &channel);
        ~Ball();
        void build();
        void send();
        void sendUpdate();
        int update();
    public:
        uint32_t _id = 0;
        Haze::Entity *_entity = nullptr;
    private:

        Haze::Engine &_engine;
        network::data_channel<protocol::data> &_channel;
};
