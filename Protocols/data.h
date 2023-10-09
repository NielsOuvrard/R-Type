#pragma once

#include <cstdint>

namespace protocol
{
    enum class UDPProtocol : std::uint32_t {
        alive,
        acknowledge,
    };
}