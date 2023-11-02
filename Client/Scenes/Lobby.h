//
// Created by erwan on 10/28/23.
//

#pragma once

#include "../Elements/Element.h"
#include "../Elements/UserCard.h"
#include <array>

class Lobby : public Element {
public:
    explicit Lobby(Haze::Engine &engine);
    void update() override;
    void build() override;

    std::array<UserCard, 4> players;
};
