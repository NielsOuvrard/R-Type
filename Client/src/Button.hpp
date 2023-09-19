#include <SFML/Graphics.hpp>
#include <iostream>

class Button
{
public:
    Button(sf::Vector2f position, sf::Vector2f size, sf::Font font);

    void handleEvent(sf::Event event, sf::RenderWindow &window);
    void update();
    void render(sf::RenderWindow &window);

    bool isClicked() const;
    bool isHeld() const;

private:
    sf::RectangleShape _buttonShape;
    sf::Text _buttonText;
    sf::Font _font;
    bool _isClickedState;
    bool _isHeldState;
};

Button::Button(sf::Vector2f position, sf::Vector2f size, sf::Font font) : _font(font)
{

    _buttonShape.setPosition(position);
    _buttonShape.setSize(size);
    _buttonShape.setFillColor(sf::Color::Green);
    _isClickedState = false;
    _isHeldState = false;

    _buttonText.setFont(_font);
    _buttonText.setCharacterSize(24);
    _buttonText.setString("Press it");
    _buttonText.setStyle(sf::Text::Bold);
    _buttonText.setOutlineColor(sf::Color::Black);

    // Center the text within the button
    sf::FloatRect textBounds = _buttonText.getLocalBounds();
    _buttonText.setOrigin(textBounds.left + textBounds.width / 2.0f, textBounds.top + textBounds.height / 2.0f);
    _buttonText.setPosition(position.x + size.x / 2.0f, position.y + size.y / 2.0f);
}

void Button::handleEvent(sf::Event event, sf::RenderWindow &window)
{
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    if (_isHeldState)
    {
        _buttonShape.setFillColor(sf::Color::Blue);
    }
    else if (_buttonShape.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos)))
    {
        _buttonShape.setFillColor(sf::Color::Red);
    }
    else
    {
        _buttonShape.setFillColor(sf::Color::Green);
    }

    if (event.type == sf::Event::MouseButtonPressed)
    {
        if (event.mouseButton.button == sf::Mouse::Left)
        {
            if (_buttonShape.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos)))
            {
                _isHeldState = true;
                _buttonText.setString("Hold it");
            }
        }
    }
    else if (event.type == sf::Event::MouseButtonReleased)
    {
        if (event.mouseButton.button == sf::Mouse::Left)
        {
            _isHeldState = false;
            if (_buttonShape.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos)))
            {
                _isClickedState = true;
            }
            _buttonText.setString("Press it");
        }
    }
}

void Button::update()
{
    // You can add more functionality here as needed
}

void Button::render(sf::RenderWindow &window)
{
    window.draw(_buttonShape);
    window.draw(_buttonText);
}

bool Button::isClicked() const
{
    return _isClickedState;
}

bool Button::isHeld() const
{
    return _isHeldState;
}