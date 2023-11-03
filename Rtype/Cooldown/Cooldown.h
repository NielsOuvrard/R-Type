//
// Created by erwan on 10/15/23.
//

#pragma once

#include <chrono>
#include <iostream>

/**
 * @class Cooldown
 *
 * @brief Represents a cooldown timer for managing time-based events.
 *
 * The `Cooldown` class provides functionality to manage time-based cooldowns, allowing you to
 * control when specific events or actions can occur.
 */
class Cooldown {
public:
    /**
     * @brief Constructs a Cooldown object with the specified duration.
     *
     * @param duration The duration of the cooldown timer in milliseconds.
     */
    Cooldown(std::chrono::milliseconds duration);

    /**
     * @brief Sets the duration of the cooldown timer.
     *
     * @param duration The new duration of the cooldown timer in milliseconds.
     */
    void setDuration(std::chrono::milliseconds duration);

    /**
     * @brief Checks if the cooldown timer is ready (expired).
     *
     * @return `true` if the cooldown timer has expired and is ready; otherwise, `false`.
     */
    bool IsReady();

    /**
     * @brief Activates the cooldown timer.
     *
     * This function resets the cooldown timer and starts the countdown.
     */
    void Activate();

    /**
     * @brief Resets the cooldown timer.
     *
     * This function resets the cooldown timer, stopping the countdown.
     */
    void Reset();

private:
    std::chrono::steady_clock::time_point _lastActivation;///< The time of the last activation.
    std::chrono::milliseconds _duration;                  ///< The duration of the cooldown timer.
};
