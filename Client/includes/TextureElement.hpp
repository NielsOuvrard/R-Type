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
** TextureElement
*/

#include "InetrfaceElement.hpp"

class TextureElement : public InetrfaceElement
{
public:
    TextureElement(
        size_t id,
        std::string path)
    {
        _id = id;
        _texture = sf::Texture();
        _texture.loadFromFile(path);
        _texture.setSmooth(false);
    }

    void render(sf::RenderWindow &window) override
    {
        std::cout << "You're trying to render a texture..." << std::endl;
        std::cout << "You should think about your code skills bro..." << std::endl;
    }

    sf::Texture &getTexture()
    {
        return _texture;
    }

    void handleEvent(sf::Event event, sf::RenderWindow &window) override{};

    // data
    sf::Texture _texture;
};
