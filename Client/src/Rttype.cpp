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
    Haze::Window *window = new Haze::Window(800, 600);

    Haze::Collision::CollisionInfo colisionInfo;
    colisionInfo.type = Haze::Collision::LAMBDA;
    colisionInfo.tics = 1;
    colisionInfo.onCollision = [](int x, int y) {
        std::cout << "collision!" << std::endl;
    };
    std::map<std::string, Haze::Collision::CollisionInfo> infos = {
        {"wall", colisionInfo},
    };
    // infos["ennemy"] = Haze::Collision::CollisionInfo(0, 0, 33, 36);

    entityVortex = engine.createEntity();
    entitySpaceship = engine.createEntity();
    entityEnnemy = engine.createEntity();
    entityWindow = engine.createEntity();
    entityWallTop = engine.createEntity();

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
    entitySpaceship->addComponent(new Haze::Hitbox({{
        0, 0, 32, 14
    }}));
    entitySpaceship->addComponent(new Haze::HitboxDisplay());
    entitySpaceship->addComponent(new Haze::Collision("player", infos));

    wall1 = new wall(&engine, jsonData, 0, 600);
    wall2 = new wall(&engine, jsonData, 192, 600);
    wall3 = new wall(&engine, jsonData, 384, 600);
    wall4 = new wall(&engine, jsonData, 576, 600);
    wall5 = new wall(&engine, jsonData, 768, 600);
    wall6 = new wall(&engine, jsonData, 950, 600);
    entityEnnemy->addComponent(new Haze::Position(500, 200));
    entityEnnemy->addComponent(new Haze::Velocity(0, 0));
    entityEnnemy->addComponent(new Haze::Scale(3, 3));
    entityEnnemy->addComponent(new Haze::Animation(*ennemySprite, 0, 0, 33, 36, 8, 1, true));
    entityEnnemy->addComponent(ennemySprite);


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
    Haze::Position *position1 = static_cast< Haze::Position *>(wall1->_entityWallBottom->getComponent("Position"));
    Haze::Position *position2 = static_cast< Haze::Position *>(wall2->_entityWallBottom->getComponent("Position"));
    Haze::Position *position3 = static_cast< Haze::Position *>(wall3->_entityWallBottom->getComponent("Position"));
    Haze::Position *position4 = static_cast< Haze::Position *>(wall4->_entityWallBottom->getComponent("Position"));
    Haze::Position *position5 = static_cast< Haze::Position *>(wall5->_entityWallBottom->getComponent("Position"));
    Haze::Position *position6 = static_cast< Haze::Position *>(wall6->_entityWallBottom->getComponent("Position"));

    if (position1->x <= -200) {
        position1->x = 800;
        wall1->changeSpriteBack(wall1->_entityWallBottom);
    }
    if (position2->x <= -200) {
        position2->x = 800;
        wall2->changeSpriteBack(wall2->_entityWallBottom);
    }
    if (position3->x <= -200) {
        position3->x = 800;
        wall3->changeSpriteBack(wall3->_entityWallBottom);
    }
    if (position4->x <= -200) {
        position4->x = 800;
        wall4->changeSpriteBack(wall4->_entityWallBottom);
    }
    if (position5->x <= -200) {
        position5->x = 800;
        wall5->changeSpriteBack(wall5->_entityWallBottom);
    }
    if (position6->x <= -200) {
        position6->x = 800;
        wall6->changeSpriteBack(wall6->_entityWallBottom);
    }
}

void Rttype::run()
{
    while (engine.isOpen())
    {
        moveSpaceship();
// input events
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
        Rttype::moveBackground();
        engine.update();
    }
    std::cout << "engine closed!" << std::endl;
}
