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
** Rtype
*/

#include "Rtype.hpp"
#include "net_data_channel.h"
#include "net_server.h"
#include "data.h"

Rtype::Rtype(asio::io_context &context) : network::data_channel<protocol::UDPProtocol>(context)
{
    engine.init();
    std::ifstream inputFile("Rtype/SpritesMooves/ground.json");
    if (inputFile.is_open())
    {
        inputFile >> jsonData;
        inputFile.close();
        sheet = jsonData["sheet1"];
    }
    else
    {
        std::cout << "Impossible d'ouvrir le fichier !" << std::endl;
        exit(84);
    }

    Haze::Velocity *velocityPlayer = new Haze::Velocity(0, 0);
    Haze::Sprite *vortexSprite = new Haze::Sprite("assets/r-typesheet30a.gif");
    Haze::Sprite *shotSprite = new Haze::Sprite("assets/shot.png");
    Haze::Sprite *spaceshipSprite = new Haze::Sprite("assets/r-typesheet1.gif");
    Haze::Sprite *ennemySprite = new Haze::Sprite("assets/r-typesheet5.gif");
    Haze::Window *window = new Haze::Window(800, 600);

    Haze::Collision::CollisionInfo colisionInfo;
    colisionInfo.type = Haze::Collision::LAMBDA;
    colisionInfo.tics = 1;
    colisionInfo.onCollision = [](int x, int y)
    {
        std::cout << "collision!" << std::endl;
    };
    std::map<std::string, Haze::Collision::CollisionInfo> infos = {
        {"wall", colisionInfo},
    };
    // infos["ennemy"] = Haze::Collision::CollisionInfo(0, 0, 33, 36);

    entityVortex = engine.createEntity();
    entityShot = engine.createEntity();
    entitySpaceship = engine.createEntity();
    entityEnnemy = engine.createEntity();
    entityWindow = engine.createEntity();
    entityWallTop = engine.createEntity();

    entityVortex->addComponent(new Haze::Position(120, 200));
    entityVortex->addComponent(new Haze::Velocity(2, 0));
    entityVortex->addComponent(new Haze::Scale(3, 3));
    entityVortex->addComponent(vortexSprite);
    // entityVortex->addComponent(new Haze::Animation(*vortexSprite, 0, 0, 34, 34, 3, 1));
    entityVortex->addComponent(new Haze::Animation({{0, 0, 34, 34},
                                                    {34, 0, 34, 34},
                                                    {68, 0, 34, 34}},
                                                   Haze::Animation::AnimationType::LOOP, true, 0.2));

    entityShot->addComponent(new Haze::Position(100, 200));
    entityShot->addComponent(new Haze::Velocity(2, 0));
    entityShot->addComponent(new Haze::Scale(3, 3));
    // x = 3 * 16
    // y = 1 * 14
    entityShot->addComponent(new Haze::Animation({{0, 0, 16, 14},
                                                  {16, 0, 16, 14},
                                                  {32, 0, 16, 14}},
                                                 Haze::Animation::AnimationType::LOOP, true, 0.2));
    entityShot->addComponent(shotSprite);

    entitySpaceship->addComponent(velocityPlayer);
    entitySpaceship->addComponent(new Haze::Position(100, 200));
    entitySpaceship->addComponent(new Haze::Scale(3, 3));
    entitySpaceship->addComponent(spaceshipSprite);
    // entitySpaceship->addComponent(new Haze::Animation(*spaceshipSprite, 100, 0, 33, 18, 5, 1, true));
    entitySpaceship->addComponent(new Haze::Animation({{100, 0, 33, 18},
                                                       {133, 0, 33, 18},
                                                       {166, 0, 33, 18},
                                                       {199, 0, 33, 18},
                                                       {232, 0, 33, 18}},
                                                      Haze::Animation::AnimationType::BOOMERANG, true, 0.2));
    entitySpaceship->addComponent(new Haze::Hitbox({{0, 0, 32, 14}}));
    entitySpaceship->addComponent(new Haze::HitboxDisplay());
    entitySpaceship->addComponent(new Haze::Collision("player", infos));

    entitySpaceship->addComponent(new Haze::OnKeyPressed([this](int i, std::vector<Haze::InputType> components)
                                                         {
        if (std::find(components.begin(), components.end(), Haze::InputType::KEY_ENTER_INPUT) != components.end()) {
            Haze::Entity *newShot = engine.createEntity();
            auto position = static_cast<Haze::Position *>(entitySpaceship->getComponent("Position"));
            newShot->addComponent(new Haze::Position(position->x + 33 * 3, position->y));
            newShot->addComponent(new Haze::Velocity(2, 0));
            newShot->addComponent(static_cast<Haze::Sprite *>(entityShot->getComponent("Sprite")));
            newShot->addComponent(new Haze::Animation({{0, 0, 16, 14},
                                                      {16, 0, 16, 14},
                                                      {32, 0, 16, 14}},
                                                      Haze::Animation::AnimationType::LOOP, true, 0.2));
        }

        auto velocity = static_cast<Haze::Velocity *>(entitySpaceship->getComponent("Velocity"));
        if (velocity == nullptr)
            entitySpaceship->addComponent(new Haze::Velocity(0, 0));
        velocity->x = 0;
        velocity->y = 0;

        if (std::find(components.begin(), components.end(), Haze::InputType::KEY_UP_ARROW) != components.end()) {
            velocity->y += -5;
        }
        if (std::find(components.begin(), components.end(), Haze::InputType::KEY_LEFT_ARROW) != components.end()) {
            velocity->x += -5;
        }
        if (std::find(components.begin(), components.end(), Haze::InputType::KEY_DOWN_ARROW) != components.end()) {
            velocity->y += 5;
        }
        if (std::find(components.begin(), components.end(), Haze::InputType::KEY_RIGHT_ARROW) != components.end()) {
            velocity->x += 5;
        }
    }));



    wall1 = new wall(&engine, jsonData, 0, 600);
    wall2 = new wall(&engine, jsonData, 192, 600);
    wall3 = new wall(&engine, jsonData, 384, 600);
    wall4 = new wall(&engine, jsonData, 576, 600);
    wall5 = new wall(&engine, jsonData, 768, 600);
    wall6 = new wall(&engine, jsonData, 950, 600);
    entityEnnemy->addComponent(new Haze::Position(500, 200));
    entityEnnemy->addComponent(new Haze::Velocity(0, 0));
    entityEnnemy->addComponent(new Haze::Scale(3, 3));
    // entityEnnemy->addComponent(new Haze::Animation(*ennemySprite, 0, 0, 33, 36, 8, 1, true));
    entityEnnemy->addComponent(new Haze::Animation({{0, 0, 33, 36},
                                                    {33, 0, 33, 36},
                                                    {66, 0, 33, 36},
                                                    {99, 0, 33, 36},
                                                    {132, 0, 33, 36},
                                                    {165, 0, 33, 36},
                                                    {198, 0, 33, 36},
                                                    {231, 0, 33, 36}},
                                                   Haze::Animation::AnimationType::BOOMERANG, true, 0.2));
    entityEnnemy->addComponent(ennemySprite);

    entityWindow->addComponent(window);

#ifdef USE_SFML
    window->window.setFramerateLimit(60);
#endif
}

Rtype::~Rtype()
{
}

void Rtype::keyPress()
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

void Rtype::keyRelease()
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

void Rtype::moveBackground()
{
    Haze::Position *position1 = static_cast<Haze::Position *>(wall1->_entityWallBottom->getComponent("Position"));
    Haze::Position *position2 = static_cast<Haze::Position *>(wall2->_entityWallBottom->getComponent("Position"));
    Haze::Position *position3 = static_cast<Haze::Position *>(wall3->_entityWallBottom->getComponent("Position"));
    Haze::Position *position4 = static_cast<Haze::Position *>(wall4->_entityWallBottom->getComponent("Position"));
    Haze::Position *position5 = static_cast<Haze::Position *>(wall5->_entityWallBottom->getComponent("Position"));
    Haze::Position *position6 = static_cast<Haze::Position *>(wall6->_entityWallBottom->getComponent("Position"));

    if (position1->x <= -200)
    {
        position1->x = 800;
        wall1->changeSpriteBack(wall1->_entityWallBottom);
    }
    if (position2->x <= -200)
    {
        position2->x = 800;
        wall2->changeSpriteBack(wall2->_entityWallBottom);
    }
    if (position3->x <= -200)
    {
        position3->x = 800;
        wall3->changeSpriteBack(wall3->_entityWallBottom);
    }
    if (position4->x <= -200)
    {
        position4->x = 800;
        wall4->changeSpriteBack(wall4->_entityWallBottom);
    }
    if (position5->x <= -200)
    {
        position5->x = 800;
        wall5->changeSpriteBack(wall5->_entityWallBottom);
    }
    if (position6->x <= -200)
    {
        position6->x = 800;
        wall6->changeSpriteBack(wall6->_entityWallBottom);
    }
}

void Rtype::run(std::shared_ptr<network::data_channel<protocol::UDPProtocol>> dataChannel)
{
    _dataChannel = std::move(dataChannel);
    while (engine.isOpen())
    {
        Rtype::moveBackground();
        engine.update();
    }
    std::cout << "engine closed!" << std::endl;
}
