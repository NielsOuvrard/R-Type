//
// Created by erwan on 10/10/23.
//

#pragma once

#include "Cooldown.h"
#include "Factory.hpp"
#include "data.h"
#include "haze-core.hpp"
#include "haze-graphics.hpp"
#include "net_data_channel.h"
#include <chrono>

using namespace protocol;
using namespace std::chrono_literals;

class spectator : public network::data_channel<data> {
public:
    explicit spectator(asio::io_context &context, Haze::Engine &engine);
    void onReceive(udp::endpoint from, network::datagram<data> content) override;

public:
    void createEntity(Haze::entity_id id);
    void deleteEntity(Haze::entity_id id);
    void addComponent(Haze::component_info info);
    void removeComponent(Haze::component_id id);
    // !Unused
    //    void infoComponent();
    //    void infoEntity();
    //    void infoEntities();

    Cooldown aliveCD{5s};

private:
    Haze::Engine &_engine;
    Haze::Entity *_inputGrabber;
    std::map<uint32_t, Haze::Entity *> _entities;
};
