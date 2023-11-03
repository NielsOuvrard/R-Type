//
// Created by erwan on 10/20/23.
//

#include "Image.h"

Image::Image(Haze::Engine &engine, const std::string &filepath, Element::AxisPair position, Element::AxisPair scale)
    : Element(engine), _filepath(filepath)
{
    _position = position;
    _scale = scale;
}

void Image::build()
{
    Element::buildEntity();
    _entity->addComponent(new Haze::Sprite(_filepath));
}

void Image::update()
{
}
