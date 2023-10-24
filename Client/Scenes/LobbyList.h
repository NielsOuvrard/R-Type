//
// Created by erwan on 10/24/23.
//

#pragma once

#include "../Elements/Element.h"

class LobbyList : public Element {
public:
    LobbyList(Haze::Engine &engine, std::function<void(int)> join);

public:
    void build() override;
    void update() override;
    std::function<void(int)> _join;
};
