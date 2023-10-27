//
// Created by erwan on 10/25/23.
//

#pragma once

#include "../Elements/Button.h"
#include "../Elements/Element.h"

class LobbyItem : public Element {
public:
    LobbyItem(Haze::Engine &engine, int id, int nbRight, int nbLeft, std::function<void(uint32_t)> selectLobby);
    void build() override;
    void update() override;

    void setX(float x);
    void setY(float y);

    int _id;
    int _nbLeft;
    int _nbRight;
    bool dead = false;
    std::function<void(uint32_t)> _selectLobby;
};
