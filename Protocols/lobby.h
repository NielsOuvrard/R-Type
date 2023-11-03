#pragma once

#include <cstdint>

namespace protocol {
    enum class lobby : std::uint32_t {
        // Client
        create_room,
        get_rooms,
        get_room,
        get_chats,
        join_room,
        leave_room,
        start_room,

        // Server
        ok,
        ko,
        new_chat,
        data_channel,
    };
}// namespace protocol
