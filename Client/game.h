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

    void createEntity(Haze::entity_id id);
    void deleteEntity(Haze::entity_id id);
    void addComponent(Haze::component_info info);
    void removeComponent(Haze::component_id id);
    // !Unused
    //    void infoComponent();
    //    void infoEntity();
    //    void infoEntities();

private:
    Haze::Engine &_engine;
    std::map<uint32_t, Haze::Entity *> _entities;
};
