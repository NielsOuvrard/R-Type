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
#include "data.h"
#include "net_data_channel.h"
#include "net_server.h"

Rtype::Rtype(asio::io_context &context) : network::data_channel<protocol::data>(context)
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

    for (int i = 0; i < 7; i++) // from VORTEX to BACKGROUND
    {
        entities.push_back(engine.createEntity());
    }

    entities[VORTEX]->addComponent(new Haze::Position(120, 200));
    entities[VORTEX]->addComponent(new Haze::Velocity(2, 0));
    entities[VORTEX]->addComponent(new Haze::Scale(3, 3));
    entities[VORTEX]->addComponent(vortexSprite);
    // entities[VORTEX]->addComponent(new Haze::Animation(*vortexSprite, 0, 0, 34, 34, 3, 1));
    entities[VORTEX]->addComponent(new Haze::Animation({{0, 0, 34, 34},
                                                        {34, 0, 34, 34},
                                                        {68, 0, 34, 34}},
                                                       Haze::Animation::AnimationType::LOOP, true, 0.2));

    entities[SHOT]->addComponent(new Haze::Position(100, 200));
    entities[SHOT]->addComponent(new Haze::Velocity(2, 0));
    entities[SHOT]->addComponent(new Haze::Scale(3, 3));
    // x = 3 * 16
    // y = 1 * 14
    entities[SHOT]->addComponent(new Haze::Animation({{0, 0, 16, 14},
                                                      {16, 0, 16, 14},
                                                      {32, 0, 16, 14}},
                                                     Haze::Animation::AnimationType::LOOP, true, 0.2));
    entities[SHOT]->addComponent(shotSprite);

    entities[SPACESHIP]->addComponent(velocityPlayer);
    entities[SPACESHIP]->addComponent(new Haze::Position(100, 200));
    entities[SPACESHIP]->addComponent(new Haze::Scale(3, 3));
    entities[SPACESHIP]->addComponent(spaceshipSprite);
    // entities[SPACESHIP]->addComponent(new Haze::Animation(*spaceshipSprite, 100, 0, 33, 18, 5, 1, true));
    entities[SPACESHIP]->addComponent(new Haze::Animation({{100, 0, 33, 18},
                                                           {133, 0, 33, 18},
                                                           {166, 0, 33, 18},
                                                           {199, 0, 33, 18},
                                                           {232, 0, 33, 18}},
                                                          Haze::Animation::AnimationType::BOOMERANG, true, 0.2));
    entities[SPACESHIP]->addComponent(new Haze::Hitbox({{0, 0, 32, 14}}));
    entities[SPACESHIP]->addComponent(new Haze::HitboxDisplay());
    entities[SPACESHIP]->addComponent(new Haze::Collision("player", infos));
    entities[SPACESHIP]->addComponent(new Haze::OnKeyPressed([this](int i, std::vector<Haze::InputType> components)
                                                             {
    if (std::find(components.begin(), components.end(), Haze::InputType::KEY_ENTER_INPUT) != components.end()) {
        Haze::Entity *newShot = engine.createEntity();
        auto position = static_cast<Haze::Position *>(entities[SPACESHIP]->getComponent("Position"));
        newShot->addComponent(new Haze::Position(position->x + 33 * 3, position->y));
        newShot->addComponent(new Haze::Velocity(2, 0));
        newShot->addComponent(static_cast<Haze::Sprite *>(entities[SHOT]->getComponent("Sprite")));
        newShot->addComponent(new Haze::Animation({{0, 0, 16, 14},
                                                    {16, 0, 16, 14},
                                                    {32, 0, 16, 14}},
                                                    Haze::Animation::AnimationType::LOOP, true, 0.2));
    }

    auto velocity = static_cast<Haze::Velocity *>(entities[SPACESHIP]->getComponent("Velocity"));
    if (velocity == nullptr)
        entities[SPACESHIP]->addComponent(new Haze::Velocity(0, 0));
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
    } }));

    walls.push_back(new wall(&engine, jsonData, 0, 600));
    walls.push_back(new wall(&engine, jsonData, 192, 600));
    walls.push_back(new wall(&engine, jsonData, 384, 600));
    walls.push_back(new wall(&engine, jsonData, 576, 600));
    walls.push_back(new wall(&engine, jsonData, 768, 600));
    walls.push_back(new wall(&engine, jsonData, 950, 600));

    entities[ENNEMY]->addComponent(new Haze::Position(500, 200));
    entities[ENNEMY]->addComponent(new Haze::Velocity(0, 0));
    entities[ENNEMY]->addComponent(new Haze::Scale(3, 3));
    // entities[ENNEMY]->addComponent(new Haze::Animation(*ennemySprite, 0, 0, 33, 36, 8, 1, true));
    entities[ENNEMY]->addComponent(new Haze::Animation({{0, 0, 33, 36},
                                                        {33, 0, 33, 36},
                                                        {66, 0, 33, 36},
                                                        {99, 0, 33, 36},
                                                        {132, 0, 33, 36},
                                                        {165, 0, 33, 36},
                                                        {198, 0, 33, 36},
                                                        {231, 0, 33, 36}},
                                                       Haze::Animation::AnimationType::BOOMERANG, true, 0.2));
    entities[ENNEMY]->addComponent(ennemySprite);

    entities[WINDOW]->addComponent(window);

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
    for (int i = 0; i < 6; ++i)
    {
        Haze::Position *position = static_cast<Haze::Position *>(walls[i]->_entityWallBottom->getComponent("Position"));

        if (position->x <= -200)
        {
            position->x = 800;
            walls[i]->changeSpriteBack(walls[i]->_entityWallBottom);
        }
    }
}

void Rtype::run(std::shared_ptr<network::data_channel<protocol::data>> dataChannel)
{
    _dataChannel = std::move(dataChannel);
    while (engine.isOpen())
    {
        Rtype::moveBackground();
        engine.update();
    }
    std::cout << "engine closed!" << std::endl;
}

void Rtype::onReceive(udp::endpoint from, network::datagram<protocol::data> content)
{
    switch (content.header.id)
    {
    case protocol::data::create_entity:
        // tell to every client to create an entity, with the id of the entity
        break;
    case protocol::data::delete_entity:
        // tell to every client to delete an entity, with the id of the entity
        break;
    case protocol::data::add_component:
        // Haze::info_component info;
        // std::memcpy(&info, content.body.data(), content.header.size);
        // addComponent();
        break;
    case protocol::data::remove_component:
        break;
    }
    // ...
}
