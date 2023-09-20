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
** SoundElement
*/

#include "InetrfaceElement.hpp"

class SoundElement : public InetrfaceElement
{
public:
    SoundElement(size_t id, std::string &path)
    {
        _sound = sf::Sound();
        // _sound.setBuffer(sf::SoundBuffer());
        // _sound.getBuffer().loadFromFile(path);
        // _sound.setLoop(true);
        _id = id;
    }
    void render(sf::RenderWindow &window) override
    {
        // _sound.play();
    }

    // data
    sf::Sound _sound;
};