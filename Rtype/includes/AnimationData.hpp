/*
** ooooooooo.           ooooooooooooo
** `888   `Y88.         8'   888   `8
**  888   .d88'              888      oooo    ooo oo.ooooo.   .ooooo.
**  888ooo88P'               888       `88.  .8'   888' `88b d88' `88b
**  888`88b.    8888888      888        `88..8'    888   888 888ooo888
**  888  `88b.               888         `888'     888   888 888    .o
** o888o  o888o             o888o         .8'      888bod8P' `Y8bod8P'
**                                    .o..P'       888
**                                    `Y8P'       o888o
**
** Animation
*/

#pragma once

#include "InetrfaceElement.hpp"

class Animation
{
public:
    Animation() = default;
    Animation(std::string path, int speed, size_t height, size_t width, size_t framesX, size_t framesY)
        : _speed(speed), _height(height), _width(width), _framesX(framesX), _framesY(framesY)
    {
        _texture = sf::Texture();
        _sprite = sf::Sprite();
        if (!_texture.loadFromFile(path))
        {
            std::cout << "Error loading texture" << std::endl;
            return;
        }
        _texture.setSmooth(false);
        _sprite.setTexture(_texture);
        _rect = sf::IntRect(0, 0, _width, _height);
        _sprite.setTextureRect(_rect);
    }

    void setTexture(sf::Texture texture)
    {
        _texture = texture;
        _sprite.setTexture(_texture);
    }

    // void render(sf::RenderWindow &window)
    // {
    //     window.draw(_sprite);
    // }

    void handleEvent(sf::Event event, sf::RenderWindow &window)
    {
        if (event.type == sf::Event::Closed)
            window.close();
    }

    sf::Sprite &getSprite()
    {
        return _sprite;
    }

    int getSpeed()
    {
        return _speed;
    }

    void anime() // todo Y
    {
        if (_rect.left >= _width * (_framesX - 1))
            _rect.left = 0;
        else
            _rect.left += _width;
        _sprite.setTextureRect(_rect);
    }

private:
    sf::Sprite _sprite;
    sf::Texture _texture;
    sf::IntRect _rect;
    int _speed;
    size_t _height;
    size_t _width;
    size_t _framesX;
    size_t _framesY;
};
