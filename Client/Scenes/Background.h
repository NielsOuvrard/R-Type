//
// Created by erwan on 10/23/23.
//

#pragma once

#include "../Elements/Element.h"

class Background : public Element {
public:
    explicit Background(Haze::Engine &engine);
    void build() override;
    void update() override;
};
