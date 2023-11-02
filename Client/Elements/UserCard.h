//
// Created by erwan on 10/31/23.
//

#pragma once

#include "Element.h"

class UserCard : public Element {
public:
    UserCard(Haze::Engine &engine, int x, int y);
    void build() override;
    void update() override;
    void setHide(bool state) override;

    int x = 0;
    int y = 0;
    std::string name = "dummy";
    bool owner = false;
    bool ready = false;
    std::function<void(const std::string &)> onKick = [](const std::string &) { std::cout << "Kick" << std::endl; };

private:
    AxisPair avatar{10, 10};
    AxisPair star{55, 3};
    AxisPair kick_img{210, 10};
    AxisPair kick_btn{210, 10};
    AxisPair txt{80, 20};
};
