//
// Created by erwan on 10/24/23.
//

#include "Text.h"

#include <utility>

void Text::build()
{
    buildEntity();
    add(new Haze::Text(_value, _color, _fontfile));
}

void Text::update()
{
}

Text::Text(Haze::Engine &engine, std::string value, std::string fontfile, Haze::Text::colorHaze color, Element::AxisPair position, Element::AxisPair scale)
    : Element(engine), _value(std::move(value)), _fontfile(std::move(fontfile)), _color(color)
{
    _position = position;
    _scale = scale;
}
