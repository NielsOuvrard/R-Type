#include "Button.hpp"
#include <iostream>

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

int main()
{
    // load font for the button
    sf::Font font;
    if (!font.loadFromFile("./Client/assets/font.ttf"))
    {
        std::cout << "Error loading font\n";
    }

    // create button
    Button button(sf::Vector2f(100, 100), sf::Vector2f(200, 50), font);

    // create window
    sf::RenderWindow window(sf::VideoMode(1280, 720), "Monitor");
    while (window.isOpen())
    {
        window.clear();
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            button.handleEvent(event, window);
        }
        button.update();
        button.render(window);
        window.display();
    }
    return 0;
}
