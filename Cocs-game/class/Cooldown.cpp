//
// Created by erwan on 10/15/23.
//

#include "Cooldown.h"

Coldown::Coldown(std::chrono::milliseconds duration)
    : _duration(duration)
{
    Reset();
}

void Coldown::Reset()
{
    _lastActivation = std::chrono::steady_clock::time_point();
}

void Coldown::Activate()
{
    _lastActivation = std::chrono::steady_clock::now();
}

void Coldown::setDuration(std::chrono::milliseconds duration)
{
    _duration = duration;
}

bool Coldown::IsReady()
{
    auto now = std::chrono::steady_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(now - _lastActivation);
    return elapsed >= _duration;
}
