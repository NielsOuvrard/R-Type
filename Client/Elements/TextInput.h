//
// Created by erwan on 10/8/23.
//

#pragma once

#include "Element.h"
#include "Engine.hpp"
#include "haze-core.hpp"
#include "haze-graphics.hpp"

class TextInput : public Element {
public:
    explicit TextInput(Haze::Engine &engine, std::string placeholder, AxisPair position = {0, 0}, AxisPair scale = {1, 1});
    void build() override;
    void update() override;
    void setValue(const std::string &newValue);
    void setPlaceholder(const std::string &newPlaceholder);
    void setHitbox(int x, int y, int width, int height);

    [[nodiscard]] const std::string &getValue() const;

    bool _focus = false;
    std::function<void(const std::string &)> onSubmit = [this](const std::string &) {
        std::cout << "SUBMIT: " << _value << std::endl;
    };

    int limit = -1;

private:
    std::string _value;
    std::string _placeholder;
    std::string _fontFile = "NotoMono.ttf";
    Haze::Text::colorHaze _fontColor = Haze::Text::WHITE;
};
