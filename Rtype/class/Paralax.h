//
// Created by erwan on 10/15/23.
//

#pragma once

#include "../protocol.h"
#include "Cooldown.h"
#include "Missile.h"
#include <componentData.hpp>
#include <data.h>
#include <haze-core.hpp>
#include <net_data_channel.h>

class Paralax {
public:
    Paralax(Haze::Engine &engine, network::data_channel<protocol::data> &channel);

    void build();
    void update();
    void send();
    void sendUpdate();

private:
    Haze::Engine &_engine;
    Haze::Entity *_bg1;
    Haze::Entity *_bg2;
    network::data_channel<protocol::data> &_channel;
};
