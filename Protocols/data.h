#pragma once

#include "haze-core.hpp"
#include <cstdint>

namespace protocol
{

    enum class recieved_by_server : std::uint32_t
    {
        input,
        get_entity,
        get_entities,
        get_component,
        alive,
    };

    enum class data : std::uint32_t
    {
        // client
        alive,
        join,

        // server
        create_entity,
        delete_entity,
        add_component,
        remove_component,
        info_component,
        info_entity,
        info_entities,
        dead,
    };
} // namespace protocol