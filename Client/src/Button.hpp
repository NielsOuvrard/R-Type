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
    sf::Color _defaultColor = sf::Color(0, 128, 0); // Green
    sf::Color _hoverColor = sf::Color(0, 255, 0);   // Light Green
    sf::Color _clickColor = sf::Color(128, 0, 0);   // Red
    sf::Color _textColor = sf::Color::White;        // Default text color
    sf::Color _clickTextColor = sf::Color::Black;   // Text color when clicked

    sf::RectangleShape _buttonShape;
    sf::Text _buttonText;
    sf::Font _font;
    bool _isClickedState;
    bool _isHeldState;
};

Button::Button(sf::Vector2f position, sf::Vector2f size, sf::Font font) : _font(font),
                                                                          _defaultColor(sf::Color(0, 128, 0)), // Initialize _defaultColor in the member initializer list
                                                                          _hoverColor(sf::Color(0, 255, 0)),   // Initialize _hoverColor in the member initializer list
                                                                          _clickColor(sf::Color(128, 0, 0)),   // Initialize _clickColor in the member initializer list
                                                                          _textColor(sf::Color::White),        // Initialize _textColor in the member initializer list
                                                                          _clickTextColor(sf::Color::Black),   // Initialize _clickTextColor in the member initializer list
                                                                          _isClickedState(false),
                                                                          _isHeldState(false)
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
    bool isMouseOver = _buttonShape.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos));

    if (_isHeldState)
    {
        _buttonShape.setFillColor(_clickColor);
        _buttonText.setFillColor(_clickTextColor);
    }
    else if (isMouseOver)
    {
        _buttonShape.setFillColor(_hoverColor);
        _buttonText.setFillColor(_textColor);
    }
    else
    {
        _buttonShape.setFillColor(_defaultColor);
        _buttonText.setFillColor(_textColor);
    }

    if (event.type == sf::Event::MouseButtonPressed)
    {
        if (event.mouseButton.button == sf::Mouse::Left)
        {
            if (isMouseOver)
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
            if (isMouseOver)
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