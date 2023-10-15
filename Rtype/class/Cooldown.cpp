//
// Created by erwan on 10/15/23.
//

#include "Cooldown.h"

Cooldown::Cooldown(std::chrono::milliseconds duration)
    : _duration(duration)
{
    Reset();
}

void Cooldown::Reset()
{
    _lastActivation = std::chrono::steady_clock::time_point::min();
}

void Cooldown::Activate()
{
    _lastActivation = std::chrono::steady_clock::now();
}

bool Cooldown::IsReady()
{
    auto currentTime = std::chrono::steady_clock::now();
    return (currentTime - _lastActivation) >= _duration;
}
