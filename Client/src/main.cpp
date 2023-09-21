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
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML Graphic Client Example");

    // add image
    Object2D object2DSprite(20, 20, 0, 1);
    Collider colliderSprite(200, 200);
    Sprite sprite("Client/assets/owl.png");
    graphicClient.addElement(&object2DSprite, nullptr, &colliderSprite, &sprite, nullptr, nullptr, nullptr, nullptr);

    // add text
    Object2D object2DText(20, 20, 0, 40);
    Text text("hello world", "Client/assets/font.ttf", 28);
    graphicClient.addElement(&object2DText, nullptr, nullptr, nullptr, &text, nullptr, nullptr, nullptr);

    // add sound
    Sound sound("Client/assets/pluck_001.ogg");
    graphicClient.addElement(nullptr, nullptr, nullptr, nullptr, nullptr, &sound, nullptr, nullptr);

    // add animation
    Object2D object2DAnimation(600, 100, 0, 5);
    Transform transformAnimation(3, 0, 0, 0);
    Animation animation("Client/assets/r-typesheet30a.gif", 1, 34, 34, 3, 1);
    graphicClient.addElement(&object2DAnimation, &transformAnimation, nullptr, nullptr, nullptr, nullptr, nullptr, &animation);

    graphicClient.run();
    return 0;
}
