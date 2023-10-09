//
// Created by erwan on 10/9/23.
//

#include "Button.h"

#include <utility>

namespace cmp {
    Button::Button(Haze::Engine &engine, std::string label, std::function<void(int)> callback)
        : _engine(engine),
          _entity(_engine.createEntity()),
          _label(std::move(label)) {
        _entity->addComponent(new Haze::Text(_label, sf::Color::White, "NotoMono.ttf"));
        _entity->addComponent(new Haze::Scale(1, 1));
        _entity->addComponent(new Haze::Hitbox({{-10, -5, 200, 50}}));
        _entity->addComponent(new Haze::HitboxDisplay);
        _entity->addComponent(new Haze::OnMouseReleased(std::move(callback)));
        _entity->addComponent(new Haze::Position(0, 0));
    }
    Haze::Entity &Button::getEntity() const {
        return *_entity;
    }
}// namespace cmp