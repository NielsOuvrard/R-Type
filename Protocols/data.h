#pragma once

#include "haze-core.hpp"
#include <cstdint>

namespace protocol {
    enum class data : std::uint32_t {
        // client
        alive,
        join,
        input,

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
}// namespace protocol