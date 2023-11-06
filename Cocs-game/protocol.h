//
// Created by erwan on 10/13/23.
//

#pragma once

#include "data.h"
#include "net_datagram.h"
#include <iostream>

namespace cocs_game {
    class message {
    public:
        static network::datagram<protocol::data> createEntity(uint32_t id)
        {
            network::datagram<protocol::data> msg(protocol::data::create_entity);
            msg.header.size = sizeof(Haze::id_entity);
            Haze::id_entity body = {id};
            std::memcpy(msg.body.data(), &body, sizeof(Haze::id_entity));
            return msg;
        };

        static network::datagram<protocol::data> deleteEntity(uint32_t id)
        {
            network::datagram<protocol::data> msg(protocol::data::delete_entity);
            msg.header.size = sizeof(Haze::id_entity);
            Haze::id_entity body = {id};
            std::memcpy(msg.body.data(), &body, sizeof(Haze::id_entity));
            return msg;
        };

        static network::datagram<protocol::data> addComponent(uint32_t id, std::string type, void *bodyData, size_t size)
        {
            network::datagram<protocol::data> msg(protocol::data::add_component);
            msg.header.size = sizeof(Haze::component_info);
            Haze::component_info info = {id, {0}, {0}};
            std::strcat(info.name, type.data());
            std::memcpy(info.data.data(), bodyData, size);
            std::memcpy(msg.body.data(), &info, sizeof(Haze::component_info));
            return msg;
        };

        static network::datagram<protocol::data> removeComponent(uint32_t id, std::string type)
        {
            network::datagram<protocol::data> msg(protocol::data::remove_component);
            msg.header.size = sizeof(Haze::component_info);
            Haze::component_info info = {id, {0}, {0}};
            std::strcat(info.name, type.data());
            std::memcpy(msg.body.data(), &info, sizeof(Haze::component_info));
            return msg;
        };
    };
}