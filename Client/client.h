//
// Created by erwan on 10/6/23.
//

#pragma once

#include "common.h"
#include "components/Login.h"
#include "haze-core.hpp"
#include "haze-graphics.hpp"
#include "net_client.h"
#include <iostream>

class client : public network::client_interface<com::lobby> {
public:
    client();
    ~client() override;

public:
    void build();
    void start();

private:
    bool _isBuild = false;
    Haze::Engine _engine;
    Haze::Entity *_window;
    std::unique_ptr<cmp::Login> _login = nullptr;
};