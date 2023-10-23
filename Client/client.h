//
// Created by erwan on 10/6/23.
//

#pragma once

#include "Elements/Element.h"
#include "data.h"
#include "haze-core.hpp"
#include "haze-graphics.hpp"
#include "lobby.h"
#include "net_client.h"
#include "net_data_channel.h"
#include "spectator.h"
#include <iostream>

class client : public network::client_interface<protocol::lobby> {
public:
    client() = default;
    ~client() override = default;

public:
    void build();
    void start();

private:
    Haze::Engine _engine;
    bool _build = false;

    Haze::Entity *_window = nullptr;
    std::unique_ptr<Element> _bg;
    std::unique_ptr<Element> _login;

    std::unique_ptr<spectator> _spectator;
};
