//
// Created by erwan on 10/15/23.
//

#pragma once

#include "../protocol.h"
#include <componentData.hpp>
#include <data.h>
#include <haze-core.hpp>
#include <net_data_channel.h>

class Missile {
public:
    Missile(Haze::Engine &engine, network::data_channel<protocol::data> &channel, Haze::Position *pos);
    void build();
    void send();
    void sendUpdate();

    Haze::Entity *entity = nullptr;

private:
    Haze::Engine &_engine;
    network::data_channel<protocol::data> &_channel;
    Haze::Position *_pos;
};
