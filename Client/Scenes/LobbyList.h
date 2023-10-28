//
// Created by erwan on 10/24/23.
//

#pragma once

#include "../Elements/Element.h"
#include "LobbyItem.h"

class LobbyList : public Element {
public:
    LobbyList(Haze::Engine &engine, uint32_t &currentLobby, std::function<void()> join, std::function<void()> create, std::function<void()> disconnect);

    std::map<uint32_t, std::unique_ptr<LobbyItem>> _items;
    void setHide(bool state) override;

public:
    void update() override;
    void build() override;
    std::function<void()> _join;
    std::function<void()> _create;
    std::function<void()> _disconnect;
    uint32_t &_currentLobby;
};
