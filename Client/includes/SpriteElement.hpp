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

class SpriteElement : public InetrfaceElement
{
public:
    SpriteElement(
        size_t id,
        int x = 0,
        int y = 0,
        double height = 0,
        double width = 0,
        int rotation = 0,
        int originX = 0,
        int originY = 0)
    {
        _id = id;

        _sprite = sf::Sprite();

        _sprite.setPosition(x, y);
        _sprite.setRotation(rotation);
        _sprite.setOrigin(originX, originY);

        _sprite.setScale(width, height);
    }

    void render(sf::RenderWindow &window) override
    {
        window.draw(_sprite);
    }

    void setTexture(const sf::Texture &texture)
    {
        _sprite.setTexture(texture);
    }

    void handleEvent(sf::Event event, sf::RenderWindow &window) override{};

    // data
    sf::Sprite _sprite;
    sf::Texture _texture;
};

// class TextureElement : public InetrfaceElement
// {
// public:
//     TextureElement(
//         size_t id,
//         int opacity = 255)
//     {
//         _id = id;
//         _texture = sf::Texture();
//     }

//     void render(sf::RenderWindow &window) override
//     {
//         std::cout << "You're trying to render a texture..." << std::endl;
//         std::cout << "You should think about your code skills bro..." << std::endl;
//     }

//     // data
//     sf::Texture _texture;
// };
