//
// Created by erwan on 10/15/23.
//

#pragma once

#include <chrono>
#include <iostream>

class Cooldown {
public:
    Cooldown(std::chrono::milliseconds duration);
    void setDuration(std::chrono::milliseconds duration);
    bool IsReady();
    void Activate();
    void Reset();

private:
    std::chrono::steady_clock::time_point _lastActivation;
    std::chrono::milliseconds _duration;
};
