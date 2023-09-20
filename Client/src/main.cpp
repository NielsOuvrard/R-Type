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

#include <iostream>

int main()
{
    std::vector<std::unique_ptr<InetrfaceElement>> elements;

    // Clovis's data :
    TextureElement textureElement(1, "Client/assets/owl.png");
    elements.push_back(std::make_unique<TextureElement>(textureElement));

    SpriteElement spriteElement(2, 200, 200, 50, 50, 0);
    spriteElement.setTexture(textureElement.getTexture());

    elements.push_back(std::make_unique<SpriteElement>(spriteElement));

    // sf::Font font;
    // if (!font.loadFromFile("./Client/assets/font.ttf"))
    // {
    //     std::cout << "Error loading font\n";
    // }
    FontElement fontElement(3, "Client/assets/font.ttf");
    elements.push_back(std::make_unique<FontElement>(fontElement));

    TextElement textElement(4, "hello world");
    textElement.setFont(fontElement.getFont());
    elements.push_back(std::make_unique<TextElement>(textElement));

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
        }
        window.display();
    }
    std::cout << "Graphic Client !" << std::endl;
    return 0;
}
