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

#include "GraphicClient.hpp"

int main()
{
    GraphicClient graphicClient;
    // Clovis's data :

    // Texture
    TextureElement textureElement(1, "Client/assets/owl.png");
    graphicClient.addElement(std::make_unique<TextureElement>(textureElement));

    // Sprite
    SpriteElement spriteElement(2, 200, 200, 0.3, 0.3, 0);
    spriteElement.setTexture(textureElement.getTexture());
    graphicClient.addElement(std::make_unique<SpriteElement>(spriteElement));

    // Font
    FontElement fontElement(3, "Client/assets/font.ttf");
    graphicClient.addElement(std::make_unique<FontElement>(fontElement));

    // Text
    TextElement textElement(4, "hello world");
    textElement.setFont(fontElement.getFont());
    graphicClient.addElement(std::make_unique<TextElement>(textElement));

    // Button
    ButtonElement buttonElement(5, 300, 300);
    buttonElement.setFont(fontElement.getFont());
    graphicClient.addElement(std::make_unique<ButtonElement>(buttonElement));

    graphicClient.run();
    return 0;
}
