//
// Created by erwan on 10/9/23.
//

#include "Button.h"

#include <utility>

Button::Button(Haze::Engine &engine, std::function<void(int)> callback, AxisPair position, AxisPair scale)
    : Element(engine), _callback(std::move(callback))
{
    _position = position;
    _scale = scale;
}

void Button::build()
{
    buildEntity();
    _entity->addComponent(new Haze::Text(_label, _fontColor, _fontFile));
    _entity->addComponent(new Haze::Position(_position.x, _position.y));
    _entity->addComponent(new Haze::Scale(_scale.x, _scale.y));
    _entity->addComponent(new Haze::Hitbox({{-10, -10, 10, 10}}));
    _entity->addComponent(new Haze::HitboxDisplay);
    _entity->addComponent(new Haze::OnMouseReleased(_callback));
}

void Button::update()
{
}

void Button::setLabel(std::string label)
{
    _label = std::move(label);
    auto t = dynamic_cast<Haze::Text *>(_entity->getComponent("Text"));
    t->text = _label;
}

void Button::setHitbox(int x, int y, int width, int height)
{
    auto hitbox = comp<Haze::Hitbox>("Hitbox");
    hitbox->hitbox[0].x = x;
    hitbox->hitbox[0].y = y;
    hitbox->hitbox[0].width = width;
    hitbox->hitbox[0].height = height;
}
