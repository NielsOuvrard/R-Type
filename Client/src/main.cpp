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
** main
*/

#include "../includes/InetrfaceElement.hpp"
#include "../includes/TextElement.hpp"
#include "../includes/FontElement.hpp"
#include "../includes/SoundElement.hpp"
#include "../includes/TextureElement.hpp"
#include "../includes/SpriteElement.hpp"
#include "../includes/ButtonElement.hpp"

int main()
{
    std::vector<std::unique_ptr<InetrfaceElement>> elements;

    // Clovis's data :

    // Texture
    TextureElement textureElement(1, "Client/assets/owl.png");
    elements.push_back(std::make_unique<TextureElement>(textureElement));

    // Sprite
    SpriteElement spriteElement(2, 200, 200, 0.3, 0.3, 0);
    spriteElement.setTexture(textureElement.getTexture());
    elements.push_back(std::make_unique<SpriteElement>(spriteElement));

    // Font
    FontElement fontElement(3, "Client/assets/font.ttf");
    elements.push_back(std::make_unique<FontElement>(fontElement));

    // Text
    TextElement textElement(4, "hello world");
    textElement.setFont(fontElement.getFont());
    elements.push_back(std::make_unique<TextElement>(textElement));

    // Button
    ButtonElement buttonElement(5, 300, 300);
    buttonElement.setFont(fontElement.getFont());
    elements.push_back(std::make_unique<ButtonElement>(buttonElement));

    // create window
    sf::RenderWindow window(sf::VideoMode(1280, 720), "Monitor");

    while (window.isOpen())
    {
        window.clear();
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
            for (const auto &elementPtr : elements)
            {
                if (auto buttonElementPtr = dynamic_cast<ButtonElement *>(elementPtr.get()))
                {
                    buttonElementPtr->handleEvent(event, window);
                }
            }
        }
        for (const auto &elementPtr : elements)
        {
            if (auto spriteElementPtr = dynamic_cast<SpriteElement *>(elementPtr.get()))
            {
                spriteElementPtr->render(window);
            }
            else if (auto textElementPtr = dynamic_cast<TextElement *>(elementPtr.get()))
            {
                textElementPtr->render(window);
            }
            else if (auto buttonElementPtr = dynamic_cast<ButtonElement *>(elementPtr.get()))
            {
                buttonElementPtr->render(window);
            }
        }
        window.display();
    }
    return 0;
}
