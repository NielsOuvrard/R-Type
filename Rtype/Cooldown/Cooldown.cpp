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
    _lastActivation = std::chrono::steady_clock::time_point();
}

void Cooldown::Activate()
{
    _lastActivation = std::chrono::steady_clock::now();
}

void Cooldown::setDuration(std::chrono::milliseconds duration)
{
    _duration = duration;
}

bool Cooldown::IsReady()
{
    auto now = std::chrono::steady_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(now - _lastActivation);
    return elapsed >= _duration;
}
