//
// Created by erwan on 10/10/23.
//

#pragma once

#include "data.h"
#include "haze-core.hpp"
#include "haze-graphics.hpp"
#include "net_data_channel.h"

using namespace protocol;

class game : public network::data_channel<data> {
public:
    explicit game(asio::io_context &context, Haze::Engine &engine);
    void onReceive(udp::endpoint from, network::datagram<data> content) override;

    void createEntity(Haze::info_component info) {}
    void deleteEntity() {}
    void addComponent() {}
    void removeComponent() {}
    void infoComponent() {}
    void infoEntity() {}
    void infoEntities() {}

private:
    Haze::Engine &_engine;
    std::list<Haze::Entity *> _entities;
};
