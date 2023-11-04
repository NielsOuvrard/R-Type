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
    client(int framerate = 60, int lib = 0)
        : _engine(framerate, lib)
    {
    }
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
        in_game,
    };

    void handleOk(network::message<lobby> &msg);
    void handleKo(network::message<lobby> &msg);
    void handleNewChat(network::message<lobby> &msg);
    void handleDataSocket(network::message<lobby> &msg);

private:
    Haze::Engine _engine;
    bool _build = false;

    Haze::Entity *_window = nullptr;
    std::map<std::string, std::shared_ptr<Element>> _elements;
    std::string _selected;

    std::unique_ptr<spectator> _spectator;
    state _state = state::ok;
    uint32_t _currentLobby = 0;
};
