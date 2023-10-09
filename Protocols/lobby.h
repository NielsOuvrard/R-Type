#pragma once

#include <cstdint>

namespace protocol
{
    enum class Lobby : std::uint32_t {
        // Request
        create_room,
        get_rooms,
        join_room,
        leave_room,
        start_room,

        // Response
        data_channel,
    };
} // namespace protocol

