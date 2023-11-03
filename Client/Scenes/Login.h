//
// Created by erwan on 10/20/23.
//a

#pragma once

#include "../Elements/Element.h"
#include "../Elements/TextInput.h"

class Login : public Element {
public:
    Login(Haze::Engine &engine, std::function<void()> connect);
    void build() override;
    void update() override;

private:
    std::function<void()> _connect;
};
