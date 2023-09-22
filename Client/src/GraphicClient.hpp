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
#include "../includes/TransformData.hpp"
#include "../includes/ColliderData.hpp"
#include "../includes/SpriteData.hpp"
#include "../includes/TextData.hpp"
#include "../includes/SoundData.hpp"
#include "../includes/AnimationData.hpp"

class GraphicClient
{
public:
    GraphicClient() = default;
    ~GraphicClient() = default;

    void run();
    void addElement(
        Object2D *object2D,
        Transform *transform,
        Collider *collider,
        Sprite *sprite,
        Text *text,
        Sound *sound,
        Music *music,
        Animation *animation)
    {
        _Object2Ds.push_back(object2D);
        _Transforms.push_back(transform);
        _Colliders.push_back(collider);
        _Sprites.push_back(sprite);
        _Texts.push_back(text);
        _Sounds.push_back(sound);
        _Musics.push_back(music);
        _Animations.push_back(animation);
    }

private:
    void render(sf::RenderWindow &window);
    void update();

    // Define the update interval (in seconds)
    sf::Clock _clock;
    float _animationInterval = 1.0f; // Update every 1 seconds
    float _transformInterval = 0.025f;
    float _timeSinceLastUpdateTransform = 0.0f;
    float _timeSinceLastUpdateAnimation = 0.0f;

    std::vector<Object2D *> _Object2Ds;
    std::vector<Transform *> _Transforms;
    std::vector<Collider *> _Colliders;
    std::vector<Sprite *> _Sprites;
    std::vector<Text *> _Texts;
    std::vector<Sound *> _Sounds;
    std::vector<Music *> _Musics;
    std::vector<Animation *> _Animations;
};

void GraphicClient::run()
{
    _clock.restart();

    sf::RenderWindow window(sf::VideoMode(1280, 720), "Monitor");
    window.setFramerateLimit(60);
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
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space)
            {
                for (int i = 0; i < _Sounds.size(); i++)
                {
                    if (_Sounds[i] == nullptr)
                        continue;
                    _Sounds[i]->play();
                }
            }
        }
        update();
        render(window);
        window.display();
    }
}

void GraphicClient::update()
{
    float deltaTime = _clock.restart().asSeconds();
    _timeSinceLastUpdateTransform += deltaTime;
    if (_timeSinceLastUpdateTransform >= _transformInterval)
    {
        for (int i = 0; i < _Transforms.size(); i++)
        {
            if (_Transforms[i] == nullptr || _Object2Ds[i] == nullptr)
                continue;
            _Object2Ds[i]->addX(_Transforms[i]->getX());
            _Object2Ds[i]->addY(_Transforms[i]->getY());
            _Object2Ds[i]->addRotation(_Transforms[i]->getRotation());
            _Object2Ds[i]->addScale(_Transforms[i]->getScale());
        }
        _timeSinceLastUpdateTransform = 0.0f;
    }
    _timeSinceLastUpdateAnimation += deltaTime;
    if (_timeSinceLastUpdateAnimation >= _animationInterval)
    {
        for (int i = 0; i < _Animations.size(); i++)
        {
            if (_Animations[i] == nullptr)
                continue;
            _Animations[i]->anime();
        }
        _timeSinceLastUpdateAnimation = 0.0f;
    }
}

void GraphicClient::render(sf::RenderWindow &window)
{
    // Sprite
    for (int i = 0; i < _Sprites.size(); i++)
    {
        if (_Sprites[i] == nullptr || _Object2Ds[i] == nullptr)
            continue;
        sf::Sprite spriteLocal = _Sprites[i]->getSprite();
        spriteLocal.setPosition(_Object2Ds[i]->getX(), _Object2Ds[i]->getY());
        spriteLocal.setRotation(_Object2Ds[i]->getRotation());
        spriteLocal.setScale(_Object2Ds[i]->getScale(), _Object2Ds[i]->getScale());
        window.draw(spriteLocal);
    }
    // Text
    for (int i = 0; i < _Texts.size(); i++)
    {
        if (_Texts[i] == nullptr || _Object2Ds[i] == nullptr)
            continue;
        sf::Text textLocal = _Texts[i]->getText();
        textLocal.setPosition(_Object2Ds[i]->getX(), _Object2Ds[i]->getY());
        textLocal.setRotation(_Object2Ds[i]->getRotation());
        // textLocal.setCharacterSize(_Texts[i]->getCharacterSize());
        window.draw(textLocal);
    }
    // Animation
    for (int i = 0; i < _Animations.size(); i++)
    {
        if (_Animations[i] == nullptr || _Object2Ds[i] == nullptr)
            continue;
        sf::Sprite animeLocal = _Animations[i]->getSprite();
        animeLocal.setPosition(_Object2Ds[i]->getX(), _Object2Ds[i]->getY());
        animeLocal.setRotation(_Object2Ds[i]->getRotation());
        animeLocal.setScale(_Object2Ds[i]->getScale(), _Object2Ds[i]->getScale());

        window.draw(animeLocal);
    }
}
