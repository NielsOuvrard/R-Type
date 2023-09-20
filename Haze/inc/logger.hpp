/*
** EPITECH PROJECT, 2023
** raytracer
** File description:
** logger
*/

#pragma once

#include "colors.hpp"

#define LOG(COLOR, WHAT, MSG) "[" << COLOR << #WHAT << RESET << "] " << MSG << std::endl

#define LOG_ENGINE(MSG) LOG(CYAN, engine, MSG)
#define LOG_ERR_ENGINE(MSG) LOG(RED, engine, MSG)

