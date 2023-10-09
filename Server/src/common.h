//
// Created by erwan on 9/29/23.
//

#ifndef AD2ECC58_9CC4_4AA0_80FC_78BD85386671
#define AD2ECC58_9CC4_4AA0_80FC_78BD85386671


#include <cstdint>

enum class Protocol : std::uint32_t {
    // Request
    create_room,
    get_rooms,
    join_room,
    leave_room,
    start_room,

    // Response
    data_channel,
};


enum class UDPProtocol : std::uint32_t {
    alive,
    acknowledge,
};


#endif /* AD2ECC58_9CC4_4AA0_80FC_78BD85386671 */
