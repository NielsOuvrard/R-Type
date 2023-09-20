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
** GraphicClient
**
*/

#include "../includes/InetrfaceElement.hpp"
#include "../includes/TextElement.hpp"
#include "../includes/FontElement.hpp"
#include "../includes/SoundElement.hpp"
#include "../includes/TextureElement.hpp"
#include "../includes/SpriteElement.hpp"
#include "../includes/ButtonElement.hpp"

class GraphicClient
{
public:
    GraphicClient() = default;
    ~GraphicClient() = default;

    void run();
    void addElement(std::unique_ptr<InetrfaceElement> elementPtr)
    {
        _elements.push_back(std::move(elementPtr));
    }

    std::vector<std::unique_ptr<InetrfaceElement>> _elements;
};

void GraphicClient::run()
{
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
            for (const auto &elementPtr : _elements)
            {
                if (auto buttonElementPtr = dynamic_cast<ButtonElement *>(elementPtr.get()))
                {
                    buttonElementPtr->handleEvent(event, window);
                }
            }
        }
        for (const auto &elementPtr : _elements)
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
}
