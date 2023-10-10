//
// Created by erwan on 10/4/23.
//

#pragma once

#include "net_common.h"
#include <algorithm>
#include <chrono>
#include <cstdint>
#include <iomanip>
#include <iostream>

namespace network {

    template<typename T>
    struct datagram_header {
        T id;
        std::uint32_t size = 0;
        std::chrono::system_clock::time_point timestamp;
    };

    template<typename T>
    struct datagram {
        datagram_header<T> header;
        std::array<uint8_t, 1024 - sizeof(datagram_header<T>)> body;

        datagram() = default;
        explicit datagram(T id) : header({id, 0, std::chrono::system_clock::now()}) {}
    };

    template<typename T>
    struct owned_datagram {
        asio::ip::udp::endpoint target;
        datagram<T> data;
    };
}// namespace network