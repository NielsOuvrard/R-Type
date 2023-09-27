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

#pragma once

#include "InetrfaceElement.hpp"

class Sound
{
public:
    Sound() = default;
    Sound(std::string path, int volume = 50, bool loop = false)
        : _volume(volume), _loop(loop)
    {
        if (!_soundBuffer.loadFromFile(path))
        {
            std::cout << "Error loading sound" << std::endl;
        }
        _sound.setBuffer(_soundBuffer);
        _sound.setVolume(_volume);
        _sound.setLoop(_loop);
    }

    void setVolume(int volume)
    {
        _volume = volume;
        _sound.setVolume(_volume);
    }
    void play() { _sound.play(); }

private:
    sf::Sound _sound;
    sf::SoundBuffer _soundBuffer;
    int _volume;
    bool _loop;
};

class Music
{
public:
    Music() = default;
    Music(std::string path, int volume = 1, bool loop = false)
        : _volume(volume), _loop(loop)
    {
        if (!_music.openFromFile(path))
        {
            std::cout << "Error loading music" << std::endl;
        }
        _music.setVolume(_volume);
        _music.setLoop(_loop);
    }

    void play() { _music.play(); }

private:
    sf::Music _music;
    sf::SoundBuffer _soundBuffer;
    int _volume;
    bool _loop;
};
