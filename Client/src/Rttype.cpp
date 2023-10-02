/*
** EPITECH PROJECT, 2023
** cpp r-type by le cocks
** File description:
** Rtype.cpp
*/

#include "Rttype.hpp"

Rttype::Rttype()
{
    engine.init();
    std::ifstream inputFile("Client/SpritesMooves/ground.json");
    if (inputFile.is_open())
    {
        inputFile >> jsonData;
        inputFile.close();
        sheet = jsonData["sheet1"];
    }
    else
    {
        std::cout << "Impossible d'ouvrir le fichier !" << std::endl;
    }

    Haze::Velocity *velocityPlayer = new Haze::Velocity(0, 0);
    Haze::Sprite *vortexSprite = new Haze::Sprite("assets/r-typesheet30a.gif");
    Haze::Sprite *spaceshipSprite = new Haze::Sprite("assets/r-typesheet1.gif");
    Haze::Sprite *ennemySprite = new Haze::Sprite("assets/r-typesheet5.gif");
    Haze::Sprite *wallSprite1 = new Haze::Sprite("assets/wall.png");
    Haze::Sprite *wallSprite2 = new Haze::Sprite("assets/wall.png");
    Haze::Sprite *wallSprite3 = new Haze::Sprite("assets/wall.png");
    Haze::Sprite *wallSprite4 = new Haze::Sprite("assets/wall.png");
    Haze::Sprite *wallSprite5 = new Haze::Sprite("assets/wall.png");
    Haze::Sprite *wallSprite6 = new Haze::Sprite("assets/wall.png");
    Haze::Window *window = new Haze::Window(800, 600);

    entityVortex = engine.createEntity();
    entitySpaceship = engine.createEntity();
    entityEnnemy = engine.createEntity();
    entityWindow = engine.createEntity();
    entityWallTop = engine.createEntity();
    entityWallBottom1 = engine.createEntity();
    entityWallBottom2 = engine.createEntity();
    entityWallBottom3 = engine.createEntity();
    entityWallBottom4 = engine.createEntity();
    entityWallBottom5 = engine.createEntity();
    entityWallBottom6 = engine.createEntity();

    entityVortex->addComponent(new Haze::Position(120, 200));
    entityVortex->addComponent(new Haze::Velocity(2, 0));
    entityVortex->addComponent(new Haze::Scale(3, 3));
    entityVortex->addComponent(vortexSprite);
    entityVortex->addComponent(new Haze::Animation(*vortexSprite, 0, 0, 34, 34, 3, 1));

    entitySpaceship->addComponent(velocityPlayer);
    entitySpaceship->addComponent(new Haze::Position(100, 200));
    entitySpaceship->addComponent(new Haze::Scale(3, 3));
    entitySpaceship->addComponent(spaceshipSprite);
    entitySpaceship->addComponent(new Haze::Animation(*spaceshipSprite, 100, 0, 33, 18, 5, 1, true));

    entityEnnemy->addComponent(new Haze::Position(500, 200));
    entityEnnemy->addComponent(new Haze::Velocity(0, 0));
    entityEnnemy->addComponent(new Haze::Scale(3, 3));
    entityEnnemy->addComponent(new Haze::Animation(*ennemySprite, 0, 0, 33, 36, 8, 1, true));
    entityEnnemy->addComponent(ennemySprite);

    entityWallBottom1->addComponent(new Haze::Position(0, 600));
    entityWallBottom1->addComponent(new Haze::Scale(3, -3));
    entityWallBottom1->addComponent(wallSprite1);
    entityWallBottom1->addComponent(new Haze::SplitSprite(*static_cast<Haze::Sprite *>(entityWallBottom1->getComponent("Sprite")), sheet["x"], sheet["y"], sheet["width"], sheet["height"]));
    entityWallBottom1->addComponent(new Haze::Velocity(-1, 0));
    changeSpriteBack(entityWallBottom1);

    entityWallBottom2->addComponent(new Haze::Position(195, 600));
    entityWallBottom2->addComponent(new Haze::Scale(3, -3));
    entityWallBottom2->addComponent(wallSprite2);
    entityWallBottom2->addComponent(new Haze::SplitSprite(*static_cast<Haze::Sprite *>(entityWallBottom2->getComponent("Sprite")), sheet["x"], sheet["y"], sheet["width"], sheet["height"]));
    entityWallBottom2->addComponent(new Haze::Velocity(-1, 0));
    changeSpriteBack(entityWallBottom2);

    entityWallBottom3->addComponent(new Haze::Position(390, 600));
    entityWallBottom3->addComponent(new Haze::Scale(3, -3));
    entityWallBottom3->addComponent(wallSprite3);
    entityWallBottom3->addComponent(new Haze::SplitSprite(*static_cast<Haze::Sprite *>(entityWallBottom3->getComponent("Sprite")), sheet["x"], sheet["y"], sheet["width"], sheet["height"]));
    entityWallBottom3->addComponent(new Haze::Velocity(-1, 0));
    changeSpriteBack(entityWallBottom3);

    entityWallBottom4->addComponent(new Haze::Position(585, 600));
    entityWallBottom4->addComponent(new Haze::Scale(3, -3));
    entityWallBottom4->addComponent(wallSprite4);
    entityWallBottom4->addComponent(new Haze::SplitSprite(*static_cast<Haze::Sprite *>(entityWallBottom4->getComponent("Sprite")), sheet["x"], sheet["y"], sheet["width"], sheet["height"]));
    entityWallBottom4->addComponent(new Haze::Velocity(-1, 0));
    changeSpriteBack(entityWallBottom4);

    entityWallBottom5->addComponent(new Haze::Position(780, 600));
    entityWallBottom5->addComponent(new Haze::Scale(3, -3));
    entityWallBottom5->addComponent(wallSprite5);
    entityWallBottom5->addComponent(new Haze::SplitSprite(*static_cast<Haze::Sprite *>(entityWallBottom5->getComponent("Sprite")), sheet["x"], sheet["y"], sheet["width"], sheet["height"]));
    entityWallBottom5->addComponent(new Haze::Velocity(-1, 0));
    changeSpriteBack(entityWallBottom5);

    entityWallBottom6->addComponent(new Haze::Position(975, 600));
    entityWallBottom6->addComponent(new Haze::Scale(3, -3));
    entityWallBottom6->addComponent(wallSprite6);
    entityWallBottom6->addComponent(new Haze::SplitSprite(*static_cast<Haze::Sprite *>(entityWallBottom6->getComponent("Sprite")), sheet["x"], sheet["y"], sheet["width"], sheet["height"]));
    entityWallBottom6->addComponent(new Haze::Velocity(-1, 0));
    changeSpriteBack(entityWallBottom6);

    // entityWallBottom->addComponent(new Haze::Position(0, 600));
    // entityWallBottom->addComponent(new Haze::Size(1920, -280));
    // wallSprite->sprite.setTextureRect(sf::IntRect(sheet["x"], sheet["y"], sheet["width"], sheet["height"]));
    // entityWallBottom->addComponent(wallSprite);

    // entityWallBottom->addComponent(new Haze::Position(0, 600));
    // entityWallBottom->addComponent(new Haze::Size(960, -140));
    // wallSprite->sprite.setTextureRect(sf::IntRect(0, 0, 480, 79));
    // entityWallBottom->addComponent(wallSprite);

    entityWindow->addComponent(window);
#ifdef USE_SFML
    window->window.setFramerateLimit(60);
#endif
}

Rttype::~Rttype()
{
}

void Rttype::moveUp(void *component)
{
    auto velocity = static_cast<Haze::Velocity *>(component);
    velocity->y -= 1;
}

void Rttype::moveDown(void *component)
{
    auto velocity = static_cast<Haze::Velocity *>(component);
    velocity->y += 1;
}

void Rttype::moveLeft(void *component)
{
    auto velocity = static_cast<Haze::Velocity *>(component);
    velocity->x -= 1;
}

void Rttype::moveRight(void *component)
{
    auto velocity = static_cast<Haze::Velocity *>(component);
    velocity->x += 1;
}

void Rttype::keyPress()
{
#ifdef USE_SFML
    if (event.type == sf::Event::KeyPressed)
    {
        if (event.key.code == sf::Keyboard::Up)
        {
            isMoving = 'U';
        }
        if (event.key.code == sf::Keyboard::Left)
        {
            isMoving = 'L';
        }
        if (event.key.code == sf::Keyboard::Down)
        {
            isMoving = 'D';
        }
        if (event.key.code == sf::Keyboard::Right)
        {
            isMoving = 'R';
        }
    }
#endif
}

void Rttype::keyRelease()
{
#ifdef USE_SFML
    if (event.type == sf::Event::KeyReleased)
    {
        if (event.key.code == sf::Keyboard::Up)
            isMoving = '\0';
        if (event.key.code == sf::Keyboard::Left)
            isMoving = '\0';
        if (event.key.code == sf::Keyboard::Down)
            isMoving = '\0';
        if (event.key.code == sf::Keyboard::Right)
            isMoving = '\0';
    }
#endif
}

void Rttype::moveSpaceship()
{
    Haze::Velocity *velocityPlayer = static_cast<Haze::Velocity *>(entitySpaceship->getComponent("Velocity"));
    Haze::Position *positionPlayer = static_cast<Haze::Position *>(entitySpaceship->getComponent("Position"));
    if (!isMoving)
    {
        velocityPlayer->x = 0;
        velocityPlayer->y = 0;
    }
    else if (isMoving == 'U')
    {
        velocityPlayer->y -= 1;
    }
    else if (isMoving == 'D')
    {
        velocityPlayer->y += 1;
    }
    else if (isMoving == 'L')
    {
        velocityPlayer->x -= 1;
    }
    else if (isMoving == 'R')
    {
        velocityPlayer->x += 1;
    }
    if (positionPlayer->x <= 0)
    {
        velocityPlayer->x = 0;
        positionPlayer->x = 1;
    }
    else if (positionPlayer->y <= 0)
    {
        positionPlayer->y = 0;
        velocityPlayer->y = 1;
    }
    else if (positionPlayer->x >= 800 - 33 * 3)
    {
        velocityPlayer->x = 0;
        positionPlayer->x = 800 - 33 * 3 - 1;
    }
    else if (positionPlayer->y >= 600 - 18 * 3)
    {
        positionPlayer->y = 600 - 18 * 3 - 1;
        velocityPlayer->y = 0;
    }
}

void Rttype::moveBackground()
{
    Haze::Position *position1 = static_cast<Haze::Position *>(entityWallBottom1->getComponent("Position"));
    Haze::Position *position2 = static_cast<Haze::Position *>(entityWallBottom2->getComponent("Position"));
    Haze::Position *position3 = static_cast<Haze::Position *>(entityWallBottom3->getComponent("Position"));
    Haze::Position *position4 = static_cast<Haze::Position *>(entityWallBottom4->getComponent("Position"));
    Haze::Position *position5 = static_cast<Haze::Position *>(entityWallBottom5->getComponent("Position"));
    Haze::Position *position6 = static_cast<Haze::Position *>(entityWallBottom6->getComponent("Position"));
    if (position1->x <= -280)
    {
        position1->x = 780;
        changeSpriteBack(entityWallBottom1);
    }
    if (position2->x <= -280)
    {
        position2->x = 780;
        changeSpriteBack(entityWallBottom2);
    }
    if (position3->x <= -280)
    {
        position3->x = 780;
        changeSpriteBack(entityWallBottom3);
    }
    if (position4->x <= -280)
    {
        position4->x = 780;
        changeSpriteBack(entityWallBottom4);
    }
    if (position5->x <= -280)
    {
        position5->x = 780;
        changeSpriteBack(entityWallBottom5);
    }
    if (position6->x <= -280)
    {
        position6->x = 780;
        changeSpriteBack(entityWallBottom6);
    }
}

void Rttype::changeSpriteBack(Haze::Entity *E)
{
    int randomNumber = std::rand() % 10 + 1;
    sheet = jsonData["sheet" + std::to_string(randomNumber)];
    auto splitSprite = static_cast<Haze::SplitSprite *>(E->getComponent("SplitSprite"));
    splitSprite->x = sheet["x"];
    splitSprite->y = sheet["y"];
    splitSprite->width = sheet["width"];
    splitSprite->height = sheet["height"];
}

void Rttype::run()
{
    while (engine.isOpen())
    {
        moveSpaceship();
// input events
#ifdef USE_SFML
        while (static_cast<Haze::Window *>(entityWindow->getComponent("Window"))->window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                static_cast<Haze::Window *>(entityWindow->getComponent("Window"))->window.close();
            }
            if (event.key.code == sf::Keyboard::Enter)
            {
                Haze::Entity *newVortex = engine.createEntity();
                auto position = static_cast<Haze::Position *>(entitySpaceship->getComponent("Position"));
                newVortex->addComponent(new Haze::Position(position->x, position->y));
                newVortex->addComponent(new Haze::Velocity(2, 0));
                // newVortex->addComponent(new Haze::Size(34 * 3, 34 * 3));
                newVortex->addComponent(static_cast<Haze::Sprite *>(entityVortex->getComponent("Sprite")));
                newVortex->addComponent(new Haze::Animation(*static_cast<Haze::Sprite *>(entityVortex->getComponent("Sprite")), 0, 0, 34, 34, 3, 1));
            }
            Rttype::keyPress();
            Rttype::keyRelease();
        }
#endif
        Rttype::moveBackground();
        engine.update();
    }
    std::cout << "engine closed!" << std::endl;
}
