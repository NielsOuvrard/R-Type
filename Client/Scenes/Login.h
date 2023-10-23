//
// Created by erwan on 10/20/23.
//

#pragma once

#include "../Elements/Element.h"
#include "../Elements/TextInput.h"

class Login : public Element {
public:
    explicit Login(Haze::Engine &engine);
    void build() override;
    void update() override;
};
