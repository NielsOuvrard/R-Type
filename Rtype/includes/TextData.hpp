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

#pragma once

#include "InetrfaceElement.hpp"

class Text
{
public:
    Text() = default;
    Text(std::string string, std::string font, int characterSize)
        : _string(string), _characterSize(characterSize)
    {
        if (!_font.loadFromFile(font))
        {
            std::cout << "Error loading font" << std::endl;
        }
        std::cout << "font loaded" << std::endl;
        _text.setFont(_font);
        _text.setString(_string);
        _text.setCharacterSize(_characterSize);
    }

    void setString(std::string string)
    {
        _string = string;
        _text.setString(_string);
    }

    void setCharacterSize(int characterSize)
    {
        _characterSize = characterSize;
        _text.setCharacterSize(_characterSize);
    }

    void render(sf::RenderWindow &window)
    {
        window.draw(_text);
    }

    void handleEvent(sf::Event event, sf::RenderWindow &window)
    {
        if (event.type == sf::Event::Closed)
            window.close();
    }

    sf::Text getText()
    {
        return _text;
    }

    int getCharacterSize()
    {
        return _characterSize;
    }

private:
    sf::Text _text;
    sf::Font _font;
    std::string _string;
    int _characterSize;
};
