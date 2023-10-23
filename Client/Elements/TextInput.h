//
// Created by erwan on 10/8/23.
//

#pragma once

#include "Element.h"
#include "Engine.hpp"
#include "haze-core.hpp"
#include "haze-graphics.hpp"

//class TextInput {
//public:
//    explicit TextInput(Haze::Engine &engine, std::string placeHolder);
//    void setValue(const std::string &val);
//    [[nodiscard]] Haze::Entity &getEntity() const;
//    [[nodiscard]] const std::string &getValue() const;
//    void setFocus(bool isFocused);
//
//private:
//    Haze::Engine &_engine;
//    Haze::Entity *_entity;
//
//    bool _isFocused = false;
//    std::string _placeHolder;
//    std::string _value;
//};

class TextInput : public Element {
public:
    explicit TextInput(Haze::Engine &engine, std::string placeholder, AxisPair position = {0, 0}, AxisPair scale = {1, 1});
    void build() override;
    void update() override;
    void setValue(const std::string &newValue);
    void setPlaceholder(const std::string &newPlaceholder);
    void setHitbox(int x, int y, int width, int height);

private:
    std::string _value;
    std::string _placeholder;
    std::string _fontFile = "NotoMono.ttf";
    Haze::Text::colorHaze _fontColor = Haze::Text::WHITE;
    bool _focus = false;
};
