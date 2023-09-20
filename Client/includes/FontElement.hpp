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
** FontElement
*/

#include "InetrfaceElement.hpp"

class FontElement : public InetrfaceElement
{
public:
    FontElement(size_t id, std::string path)
    {
        _font = sf::Font();
        _font.loadFromFile(path);
        _id = id;
    }

    void render(sf::RenderWindow &window) override
    {
        std::cout << "You're trying to render a font..." << std::endl;
        std::cout << "You should think about your code skills bro..." << std::endl;
    }

    sf::Font &getFont()
    {
        return _font;
    }

    // data
    sf::Font _font;
};