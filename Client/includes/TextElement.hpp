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
** TextElement
*/

#include "InetrfaceElement.hpp"

class TextElement : public InetrfaceElement
{
public:
    TextElement(size_t id, std::string textData)
    {
        _id = id;
        _text = sf::Text();
        _text.setString(textData);
        _text.setCharacterSize(24);
        _text.setFillColor(sf::Color::White);
        _text.setStyle(sf::Text::Bold);
    }

    void render(sf::RenderWindow &window) override
    {
        if (_isFontLoaded)
        {
            window.draw(_text);
        }
        else
        {
            std::cout << "The text font is not loaded" << std::endl;
        }
    }

    void setFont(const sf::Font &font)
    {
        _text.setFont(font);
        _isFontLoaded = true;
    }

    void handleEvent(sf::Event event, sf::RenderWindow &window) override{};

    // data
    sf::Text _text;
    bool _isFontLoaded = false;
};
