//
// Created by erwan on 10/9/23.
//

#include "Button.h"

#include <utility>

//namespace element {
//    Button::Button(Haze::Engine &engine, std::string label, std::function<void(int)> callback)
//        : _engine(engine),
//          _entity(_engine.createEntity()),
//          _label(std::move(label))
//    {
//        _entity->addComponent(new Haze::Text(_label, Haze::Text::WHITE, "NotoMono.ttf"));
//        _entity->addComponent(new Haze::Scale(1, 1));
//        _entity->addComponent(new Haze::Hitbox({{-10, -5, 200, 50}}));
//        _entity->addComponent(new Haze::HitboxDisplay);
//        _entity->addComponent(new Haze::OnMouseReleased(std::move(callback)));
//        _entity->addComponent(new Haze::Position(0, 0));
//    }
//
//    Haze::Entity &Button::getEntity() const
//    {
//        return *_entity;
//    }
//}// namespace element

Button::Button(Haze::Engine &engine, AxisPair position, AxisPair scale) : Element(engine)
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
}

void Button::update()
{
}

void Button::setLabel(std::string label)
{
    _label = std::move(label);
}

void Button::setHitbox(int x, int y, int width, int height)
{
    auto hitbox = comp<Haze::Hitbox>("Hitbox");
    hitbox->hitbox[0].x = x;
    hitbox->hitbox[0].y = y;
    hitbox->hitbox[0].width = width;
    hitbox->hitbox[0].height = height;
}
