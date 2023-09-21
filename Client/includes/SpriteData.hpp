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
** SpriteElement
*/

#include "InetrfaceElement.hpp"

class Sprite
{
public:
    Sprite()
    {
        _texture = sf::Texture();
        _sprite = sf::Sprite();
    };

    Sprite(std::string path)
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
    }

    Sprite(sf::Color color)
    {
        _texture = sf::Texture();
        _sprite = sf::Sprite();
        _color = color;
        _sprite.setColor(_color);
    }

    void setTexture(sf::Texture texture)
    {
        _texture = texture;
        _sprite.setTexture(_texture);
    }

    void render(sf::RenderWindow &window)
    {
        window.draw(_sprite);
    }

    void handleEvent(sf::Event event, sf::RenderWindow &window)
    {
        if (event.type == sf::Event::Closed)
            window.close();
    }

    sf::Sprite getSprite()
    {
        return _sprite;
    }

private:
    sf::Texture _texture;
    sf::Color _color;
    sf::Shader _shader;
    sf::Sprite _sprite;
};
