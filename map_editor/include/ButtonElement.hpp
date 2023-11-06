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
** ButtonElement
*/

#include "InetrfaceElement.hpp"

class ButtonElement : public InetrfaceElement {
public:
    ButtonElement(
            int x = 0,
            int y = 0,
            double height = 100,
            double width = 300,
            std::string text = "Press it")
    {
        _buttonShape = sf::RectangleShape(sf::Vector2f(width, height));
        _buttonShape.setPosition(x, y);
        _buttonShape.setFillColor(_defaultColor);

        _buttonText = sf::Text();
        _buttonText.setString(text);
        _buttonText.setFillColor(_textColor);
        _buttonText.setCharacterSize(16);

        _buttonSubText = sf::Text();
        _buttonSubText.setString("");
        _buttonSubText.setFillColor(_textColor);
        _buttonSubText.setCharacterSize(14);

        _buttonText.setStyle(sf::Text::Bold);
        _buttonText.setOutlineColor(sf::Color::Black);

        _buttonText.setPosition(_buttonShape.getPosition().x + 10, _buttonShape.getPosition().y + 10);
        _buttonSubText.setPosition(_buttonShape.getPosition().x + 10, _buttonShape.getPosition().y + 40);
    }

    void render(sf::RenderWindow &window) override
    {
        window.draw(_buttonShape);
        window.draw(_buttonText);
        window.draw(_buttonSubText);
    }

    void setFont(const sf::Font &font)
    {
        _buttonText.setFont(font);
        _buttonSubText.setFont(font);
    }

    void setTextString(const std::string &text)
    {
        _buttonText.setString(text);
    }

    void setSubTextString(const std::string &text)
    {
        _buttonSubText.setString(text);
    }

    void handleEvent(sf::Event event, sf::RenderWindow &window) override;
    bool isClicked() const;
    bool isHeld() const;

private:
    sf::Color _defaultColor = sf::Color(128, 128, 128);// Green
    sf::Color _hoverColor = sf::Color(0, 255, 0);      // Light Green
    sf::Color _clickColor = sf::Color(128, 0, 0);      // Red
    sf::Color _textColor = sf::Color::White;           // Default text color
    sf::Color _clickTextColor = sf::Color::Black;      // Text color when clicked

    sf::RectangleShape _buttonShape;
    sf::Text _buttonText;
    sf::Text _buttonSubText;
    bool _isClickedState = false;
    bool _isHeldState = false;
};

void ButtonElement::handleEvent(sf::Event event, sf::RenderWindow &window)
{
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    bool isMouseOver = _buttonShape.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos));

    if (_isHeldState) {
        _buttonShape.setFillColor(_clickColor);
        _buttonText.setFillColor(_clickTextColor);
    } else if (isMouseOver) {
        _buttonShape.setFillColor(_hoverColor);
        _buttonText.setFillColor(_textColor);
    } else {
        _buttonShape.setFillColor(_defaultColor);
        _buttonText.setFillColor(_textColor);
    }

    if (event.type == sf::Event::MouseButtonPressed) {
        if (event.mouseButton.button == sf::Mouse::Left) {
            if (isMouseOver) {
                _isHeldState = true;
                _buttonText.setString("Hold it");
            }
        }
    } else if (event.type == sf::Event::MouseButtonReleased) {
        if (event.mouseButton.button == sf::Mouse::Left) {
            _isHeldState = false;
            if (isMouseOver) {
                _isClickedState = true;
            }
            _buttonText.setString("Press it");
        }
    }
}

bool ButtonElement::isClicked() const
{
    return _isClickedState;
}

bool ButtonElement::isHeld() const
{
    return _isHeldState;
}