//
// Created by erwan on 10/8/23.
//

#include "TextInput.h"
#include <SFML/Graphics.hpp>
#include <utility>

namespace cmp {
    TextInput::TextInput(Haze::Engine &engine, std::string placeHolder)
        : _engine(engine),
          _entity(_engine.createEntity()),
          _placeHolder(std::move(placeHolder)) {
        _entity->addComponent(new Haze::Text(_placeHolder, sf::Color::White, "NotoMono.ttf"));
        _entity->addComponent(new Haze::Scale(1, 1));
        _entity->addComponent(new Haze::HitboxDisplay);
        _entity->addComponent(new Haze::Hitbox({{-10, -5, 200, 50}}));
        _entity->addComponent(new Haze::Position(0, 0));
        _entity->addComponent(new Haze::OnMouseReleased([this](int id) {
            _isFocused = true;
        }));
        _entity->addComponent(new Haze::OnKeyReleased([this](int id, std::vector<Haze::InputType> stroke) {
            if (!_isFocused || stroke.empty()) return;
            for (auto key: stroke) {
                std::cout << "KEY=" << key << std::endl;
                if (key <= Haze::KEY_Z) {
                    _value += static_cast<char>(key + 'a');
                } else if (key <= Haze::NUMKEY_9) {
                    _value += static_cast<char>(key - Haze::NUMKEY_0 + '0');
                } else if (key == Haze::KEY_DOT) {
                    _value += '.';
                } else if (key == Haze::KEY_SPACE) {
                    _value += ' ';
                } else if (key == Haze::KEY_BACK) {
                    if (!_value.empty())
                        _value.pop_back();
                } else if (key == Haze::KEY_ESC) {
                    _isFocused = false;
                    break;
                }
            }

            Haze::Text *textComponent = dynamic_cast<Haze::Text *>(_entity->getComponent("Text"));
            if (_value.empty())
                textComponent->text = _placeHolder;
            else
                textComponent->text = _value;
        }));
    }
    Haze::Entity &TextInput::getEntity() const {
        return *_entity;
    }
    const std::string &TextInput::getValue() const {
        return _value;
    }
    void TextInput::setFocus(bool isFocused) {
        _isFocused = isFocused;
    }

}// namespace cmp