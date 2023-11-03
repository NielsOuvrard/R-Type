//
// Created by erwan on 10/8/23.
//

#include "TextInput.h"
#include <utility>

TextInput::TextInput(Haze::Engine &engine, std::string placeholder, AxisPair position, AxisPair scale)
    : Element(engine), _placeholder(std::move(placeholder))
{
    _position = position;
    _scale = scale;
}

void TextInput::build()
{
    buildEntity();
    _entity->addComponent(new Haze::Text(_placeholder, 255, 255, 255, 100, _fontFile));
    _entity->addComponent(new Haze::HitboxDisplay);
    _entity->addComponent(new Haze::Hitbox({{-10, -5, 200, 50}}));
    _entity->addComponent(new Haze::OnMouseReleased([this](int id) {
        _focus = true;
    }));
    _entity->addComponent(new Haze::OnKeyReleased([this](int id, std::vector<Haze::InputType> stroke) {
        if (!_focus || stroke.empty()) return;
        for (auto key: stroke) {
            if (key <= Haze::KEY_Z) {
                if (limit < 0 || _value.size() < limit)
                    _value += static_cast<char>(key + 'a' - 1);
            } else if (key <= Haze::NUMKEY_9) {
                if (limit < 0 || _value.size() < limit)
                    _value += static_cast<char>(key - Haze::NUMKEY_0 + '0');
            } else if (key == Haze::KEY_DOT) {
                if (limit < 0 || _value.size() < limit)
                    _value += '.';
            } else if (key == Haze::KEY_SPACE) {
                if (limit < 0 || _value.size() < limit)
                    _value += ' ';
            } else if (key == Haze::KEY_BACK) {
                if (!_value.empty())
                    _value.pop_back();
            } else if (key == Haze::KEY_ESC) {
                _focus = false;
                break;
            } else if (key == Haze::KEY_ENTER_INPUT) {
                onSubmit(_value);
                _value.clear();
                break;
            }
        }

        setValue(_value);
    }));
}

void TextInput::setValue(const std::string &newValue)
{
    _value = newValue;
    auto txt = comp<Haze::Text>("Text");
    if (_value.empty()) {
        txt->text = _placeholder;
        txt->textObj->setColor(255, 255, 255, 128);
    } else {
        txt->text = _value;
        txt->textObj->setColor(255, 255, 255, 255);
    }
}

void TextInput::update()
{
    auto txt = comp<Haze::Text>("Text");
    if (_focus) {
        txt->text = _value + "|";
    } else {
        setValue(_value);
    }
}

void TextInput::setHitbox(int x, int y, int width, int height)
{
    auto hitbox = comp<Haze::Hitbox>("Hitbox");
    hitbox->hitbox[0].x = x;
    hitbox->hitbox[0].y = y;
    hitbox->hitbox[0].width = width;
    hitbox->hitbox[0].height = height;
}

const std::string &TextInput::getValue() const
{
    return _value;
}
