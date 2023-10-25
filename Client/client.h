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
    void receive();
    void emit();

private:
    enum class state {
        ok,
        w_cr_room,
        w_rooms,
        w_room,
        w_join,
        w_start,
    };

    void handleOk();
    void handleKo();
    void handleNewChat();
    void handleDataSocket();

private:
    Haze::Engine _engine{60};
    bool _build = false;

    Haze::Entity *_window = nullptr;
    std::map<std::string, std::unique_ptr<Element>> _elements;
    std::string selected;

    std::unique_ptr<spectator> _spectator;
    state _state = state::ok;
};
