//
// Created by erwan on 10/6/23.
//

#pragma once

#include "Elements/Login.h"
#include "data.h"
#include "haze-core.hpp"
#include "haze-graphics.hpp"
#include "lobby.h"
#include "net_client.h"
#include "net_data_channel.h"
#include <iostream>

class client : public network::client_interface<protocol::lobby> {
public:
    client();
    ~client() override;

public:
    void build();
    void start();

private:
    Haze::Engine _engine;
    bool _isBuild = false;
    bool _inGame = false;

    std::unique_ptr<network::data_channel<protocol::data>> _dataChannel = nullptr;

    // Haze GFX components
    Haze::Entity *_window;
    std::unique_ptr<element::Login> _login = nullptr;
    std::unique_ptr<element::Button> _startButton = nullptr;
};