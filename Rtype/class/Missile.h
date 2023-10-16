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
    Missile(Haze::Engine &engine, network::data_channel<protocol::data> &channel, bool fromPlayer);
    void build(float x, float y);
    void send();

    Haze::Entity *_entity = nullptr;

private:
    bool _fromPlayer;
    Haze::Engine &_engine;
    network::data_channel<protocol::data> &_channel;
};
