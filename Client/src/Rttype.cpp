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
    if (inputFile.is_open()) {
        inputFile >> jsonData;
        inputFile.close();
        sheet = jsonData["sheet1"];
    } else {
        std::cout << "Impossible d'ouvrir le fichier !" << std::endl;
    }

    Haze::Velocity *velocityPlayer = new Haze::Velocity(0, 0);
    Haze::Sprite *vortexSprite = new Haze::Sprite("assets/r-typesheet30a.gif");
    Haze::Sprite *spaceshipSprite = new Haze::Sprite("assets/r-typesheet1.gif");
    Haze::Sprite *wallSprite = new Haze::Sprite("assets/wall.png");
    Haze::Window *window = new Haze::Window(800, 600);

    entityVortex = engine.createEntity();
    entitySpaceship = engine.createEntity();
    entityWindow = engine.createEntity();
    entityWallTop = engine.createEntity();
    entityWallBottom1 = engine.createEntity();
    entityWallBottom2 = engine.createEntity();
    entityWallBottom3 = engine.createEntity();
    entityWallBottom4 = engine.createEntity();


    entityVortex->addComponent(new Haze::Position(120, 200));
    entityVortex->addComponent(new Haze::Velocity(2, 0));
    entityVortex->addComponent(new Haze::Size(34 * 3, 34 * 3));
    entityVortex->addComponent(vortexSprite);
    entityVortex->addComponent(new Haze::Animation(*vortexSprite, 0, 0, 34, 34, 3, 1));

    entitySpaceship->addComponent(velocityPlayer);
    entitySpaceship->addComponent(new Haze::Position(100, 200));

    entitySpaceship->addComponent(new Haze::Size(33 * 3, 18 * 3));
    entitySpaceship->addComponent(spaceshipSprite);
    entitySpaceship->addComponent(new Haze::Animation(*spaceshipSprite, 100, 0, 33, 18, 5, 1, true));

    entityWallBottom1->addComponent(new Haze::Position(0, 600));
    entityWallBottom1->addComponent(new Haze::Size(1920, -280));
    wallSprite->sprite.setTextureRect(sf::IntRect(sheet["x"], sheet["y"], sheet["width"], sheet["height"]));
    entityWallBottom1->addComponent(wallSprite);

    entityWallBottom2->addComponent(new Haze::Position(0, 600));
    entityWallBottom2->addComponent(new Haze::Size(1920, -280));
    wallSprite->sprite.setTextureRect(sf::IntRect(sheet["x"], sheet["y"], sheet["width"], sheet["height"]));
    entityWallBottom2->addComponent(wallSprite);

    // entityWallBottom->addComponent(new Haze::Position(0, 600));
    // entityWallBottom->addComponent(new Haze::Size(1920, -280));
    // wallSprite->sprite.setTextureRect(sf::IntRect(sheet["x"], sheet["y"], sheet["width"], sheet["height"]));
    // entityWallBottom->addComponent(wallSprite);

    // entityWallBottom->addComponent(new Haze::Position(0, 600));
    // entityWallBottom->addComponent(new Haze::Size(960, -140));
    // wallSprite->sprite.setTextureRect(sf::IntRect(0, 0, 480, 79));
    // entityWallBottom->addComponent(wallSprite);

    entityWindow->addComponent(window);
    window->window.setFramerateLimit(60);
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
}

void Rttype::keyRelease()
{
    if (event.type == sf::Event::KeyReleased) {
        if (event.key.code == sf::Keyboard::Up)
            isMoving = '\0';
        if (event.key.code == sf::Keyboard::Left)
            isMoving = '\0';
        if (event.key.code == sf::Keyboard::Down)
            isMoving = '\0';
        if (event.key.code == sf::Keyboard::Right)
            isMoving = '\0';
    }
}

void Rttype::moveSpaceship()
{
    Haze::Velocity *velocityPlayer = static_cast< Haze::Velocity *>(entitySpaceship->getComponent("Velocity"));
    Haze::Position *positionPlayer = static_cast< Haze::Position *>(entitySpaceship->getComponent("Position"));
    if (!isMoving) {
        velocityPlayer->x = 0;
        velocityPlayer->y = 0;
    }
    else if (isMoving == 'U') {
        velocityPlayer->y -= 1;
    }
    else if (isMoving == 'D') {
        velocityPlayer->y += 1;
    }
    else if (isMoving == 'L') {
        velocityPlayer->x -= 1;
    }
    else if (isMoving == 'R') {
        velocityPlayer->x += 1;
    }
    if (positionPlayer->x <= 0) {
        velocityPlayer->x = 0;
        positionPlayer->x = 1;
    }
    else if (positionPlayer->y <= 0) {
        positionPlayer->y = 0;
        velocityPlayer->y = 1;
    }
    else if (positionPlayer->x >= 800 - 33 * 3) {
        velocityPlayer->x = 0;
        positionPlayer->x = 800 - 33 * 3 - 1;
    }
    else if (positionPlayer->y >= 600 - 18 * 3) {
        positionPlayer->y = 600 - 18 * 3 - 1;
        velocityPlayer->y = 0;
    }
}

void Rttype::moveBackground(void *component)
{
    
}

void Rttype::changeSpriteBack(Haze::Entity E)
{
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    int randomNumber = std::rand() % 10 + 1;
    std::cout << "Nombre aléatoire : " << randomNumber << std::endl;
    sheet = jsonData["sheet" + randomNumber];
}

void Rttype::run()
{
    while (engine.isOpen())
    {
        moveSpaceship();
        while (static_cast< Haze::Window *>(entityWindow->getComponent("Window"))->window.pollEvent(event)) {

            if (event.type == sf::Event::Closed) {
                static_cast< Haze::Window *>(entityWindow->getComponent("Window"))->window.close();
            }
            if (event.key.code == sf::Keyboard::Enter) {
                Haze::Entity *newVortex = engine.createEntity();
                auto position = static_cast<Haze::Position *>(entitySpaceship->getComponent("Position"));
                newVortex->addComponent(new Haze::Position(position->x, position->y));
                newVortex->addComponent(new Haze::Velocity(2, 0));
                newVortex->addComponent(new Haze::Size(34 * 3, 34 * 3));
                newVortex->addComponent(static_cast<Haze::Sprite *>(entityVortex->getComponent("Sprite")));
                newVortex->addComponent(new Haze::Animation(*static_cast<Haze::Sprite *>(entityVortex->getComponent("Sprite")), 0, 0, 34, 34, 3, 1));
            }
            Rttype::keyPress();
            Rttype::keyRelease();
        }
        engine.update();
    }
}
