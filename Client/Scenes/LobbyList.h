//
// Created by erwan on 10/24/23.
//

#pragma once

#include "../Elements/Element.h"

class LobbyList : public Element {
public:
    LobbyList(Haze::Engine &engine, std::function<void()> join, std::function<void()> create, std::function<void()> disconnect);

public:
    void update() override;
    void build() override;
    std::function<void()> _join;
    std::function<void()> _create;
    std::function<void()> _disconnect;
};
