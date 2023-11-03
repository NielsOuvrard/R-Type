//
// Created by erwan on 10/9/23.
//

#pragma once

#include "Element.h"
#include "Engine.hpp"
#include "haze-core.hpp"
#include "haze-graphics.hpp"

class Button : public Element {
public:
    explicit Button(Haze::Engine &engine, std::function<void(int)> callback = {}, AxisPair position = {0, 0}, AxisPair scale = {1, 1});
    void update() override;
    void build() override;
    void setLabel(std::string label);
    void setHitbox(int x, int y, int width, int height);

private:
    std::function<void(int)> _callback;
    std::string _label;
    std::string _fontFile = "NotoMono.ttf";
    Haze::Text::colorHaze _fontColor = Haze::Text::WHITE;
};
