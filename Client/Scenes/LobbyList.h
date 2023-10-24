//
// Created by erwan on 10/24/23.
//

#pragma once

#include "../Elements/Element.h"

class LobbyList : public Element {
public:
    LobbyList(Haze::Engine &engine, std::function<void(int)> join, std::function<void(int)> disconnect);

public:
    void build() override;
    std::function<void(int)> _join;
    std::function<void(int)> _disconnect;
};
