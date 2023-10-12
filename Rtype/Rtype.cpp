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
    engine.setInfoInputs({std::vector<Haze::InputType>(), std::vector<Haze::InputType>(), Haze::MouseType::NOTHING, 0, 0}, 0);
    engine.setInfoInputs({std::vector<Haze::InputType>(), std::vector<Haze::InputType>(), Haze::MouseType::NOTHING, 0, 0}, 1);
    engine.setInfoInputs({std::vector<Haze::InputType>(), std::vector<Haze::InputType>(), Haze::MouseType::NOTHING, 0, 0}, 2);
    engine.setInfoInputs({std::vector<Haze::InputType>(), std::vector<Haze::InputType>(), Haze::MouseType::NOTHING, 0, 0}, 3);
    engine.setInfoInputs({std::vector<Haze::InputType>(), std::vector<Haze::InputType>(), Haze::MouseType::NOTHING, 0, 0}, 4);

    createEmptyClients();

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
    // Haze::Sprite *vortexSprite = new Haze::Sprite("assets/r-typesheet30a.gif");  // ? useless
    // Haze::Sprite *shotSprite = new Haze::Sprite("assets/shot.png");              // ? useless
    // Haze::Sprite *spaceshipSprite = new Haze::Sprite("assets/r-typesheet1.gif"); // ? useless
    // Haze::Sprite *ennemySprite = new Haze::Sprite("assets/r-typesheet5.gif");    // ? useless

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

    // ! USELESS FOR NOW
    entities[VORTEX]->addComponent(new Haze::Position(120, 200));
    entities[VORTEX]->addComponent(new Haze::Velocity(2, 0));
    entities[VORTEX]->addComponent(new Haze::Scale(3, 3));
    // entities[VORTEX]->addComponent(vortexSprite);
    // entities[VORTEX]->addComponent(new Haze::Animation({{0, 0, 34, 34},
    //                                                     {34, 0, 34, 34},
    //                                                     {68, 0, 34, 34}},
    //                                                    Haze::Animation::AnimationType::LOOP, true, 0.2));

    // ! DELETE THIS -> TODO
    entities[SHOT]->addComponent(new Haze::Position(100, 200));
    entities[SHOT]->addComponent(new Haze::Velocity(2, 0));
    entities[SHOT]->addComponent(new Haze::Scale(3, 3));
    // x = 3 * 16
    // y = 1 * 14
    // entities[SHOT]->addComponent(new Haze::Animation({{0, 0, 16, 14},
    //                                                   {16, 0, 16, 14},
    //                                                   {32, 0, 16, 14}},
    //                                                  Haze::Animation::AnimationType::LOOP, true, 0.2));
    // entities[SHOT]->addComponent(shotSprite);

    // ! DELETE ALL OF THIS -> CREATE PLAYER FUNCTION
    entities[SPACESHIP]->addComponent(velocityPlayer);
    entities[SPACESHIP]->addComponent(new Haze::Position(100, 200));
    entities[SPACESHIP]->addComponent(new Haze::Scale(3, 3));
    // entities[SPACESHIP]->addComponent(spaceshipSprite);
    // entities[SPACESHIP]->addComponent(new Haze::Animation({{100, 0, 33, 18},
    //                                                        {133, 0, 33, 18},
    //                                                        {166, 0, 33, 18},
    //                                                        {199, 0, 33, 18},
    //                                                        {232, 0, 33, 18}},
    //                                                       Haze::Animation::AnimationType::BOOMERANG, true, 0.2));
    entities[SPACESHIP]->addComponent(new Haze::Hitbox({{0, 0, 32, 14}}));
    entities[SPACESHIP]->addComponent(new Haze::HitboxDisplay());
    entities[SPACESHIP]->addComponent(new Haze::Collision("player", infos));
    entities[SPACESHIP]->addComponent(new Haze::OnKeyPressed(
        [this](int i, std::vector<Haze::InputType> components)
        {
            if (std::find(components.begin(), components.end(), Haze::InputType::KEY_ENTER_INPUT) != components.end())
            {
                Haze::Entity *newShot = engine.createEntity();
                auto position = static_cast<Haze::Position *>(entities[SPACESHIP]->getComponent("Position"));
                newShot->addComponent(new Haze::Position(position->x + 33 * 3, position->y));
                newShot->addComponent(new Haze::Velocity(2, 0));
                newShot->addComponent(static_cast<Haze::Sprite *>(entities[SHOT]->getComponent("Sprite")));
                // newShot->addComponent(new Haze::Animation({{0, 0, 16, 14},
                //                                            {16, 0, 16, 14},
                //                                            {32, 0, 16, 14}},
                //                                           Haze::Animation::AnimationType::LOOP, true, 0.2));
            }

            auto velocity = static_cast<Haze::Velocity *>(entities[SPACESHIP]->getComponent("Velocity"));
            if (velocity == nullptr)
                entities[SPACESHIP]->addComponent(new Haze::Velocity(0, 0));
            velocity->x = 0;
            velocity->y = 0;

            if (std::find(components.begin(), components.end(), Haze::InputType::KEY_UP_ARROW) != components.end())
            {
                velocity->y += -5;
            }
            if (std::find(components.begin(), components.end(), Haze::InputType::KEY_LEFT_ARROW) != components.end())
            {
                velocity->x += -5;
            }
            if (std::find(components.begin(), components.end(), Haze::InputType::KEY_DOWN_ARROW) != components.end())
            {
                velocity->y += 5;
            }
            if (std::find(components.begin(), components.end(), Haze::InputType::KEY_RIGHT_ARROW) != components.end())
            {
                velocity->x += 5;
            }
        }));

    walls.push_back(new wall(&engine, jsonData, 0, 600));
    walls.push_back(new wall(&engine, jsonData, 192, 600));
    walls.push_back(new wall(&engine, jsonData, 384, 600));
    walls.push_back(new wall(&engine, jsonData, 576, 600));
    walls.push_back(new wall(&engine, jsonData, 768, 600));
    walls.push_back(new wall(&engine, jsonData, 950, 600));

    // ! DELETE THIS -> LOAD FROM FILE THE LEVEL
    entities[ENNEMY]->addComponent(new Haze::Position(500, 200));
    entities[ENNEMY]->addComponent(new Haze::Velocity(0, 0));
    entities[ENNEMY]->addComponent(new Haze::Scale(3, 3));
    // entities[ENNEMY]->addComponent(new Haze::Animation({{0, 0, 33, 36},
    //                                                     {33, 0, 33, 36},
    //                                                     {66, 0, 33, 36},
    //                                                     {99, 0, 33, 36},
    //                                                     {132, 0, 33, 36},
    //                                                     {165, 0, 33, 36},
    //                                                     {198, 0, 33, 36},
    //                                                     {231, 0, 33, 36}},
    //                                                    Haze::Animation::AnimationType::BOOMERANG, true, 0.2));
    // ? can we remove sprite ? entities[ENNEMY]->addComponent(ennemySprite);

    Haze::Window *window = new Haze::Window(0, 0);
    entities[WINDOW]->addComponent(window);
}

Rtype::~Rtype()
{
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

void Rtype::createEmptyClients()
{
    asio::ip::udp::endpoint defaultEndpoint;
    std::chrono::time_point<std::chrono::high_resolution_clock> lastActivityTime = std::chrono::high_resolution_clock::now() - std::chrono::seconds(10);

    for (int i = 0; i < 4; i++)
    {
        ClientInfo newClient;
        newClient.endpoint = defaultEndpoint;
        newClient.lastActivityTime = lastActivityTime;
        newClient.id = i + 1;
        // newClient.score = 0;
        // newClient.life = 0;
        newClient.entity = nullptr;

        clients.push_back(newClient);
    }
}

void Rtype::checkInactivesClients()
{
    for (int i = 0; i < 4; i++)
    {
        if (std::chrono::duration<double>(std::chrono::high_resolution_clock::now() - clients[i].lastActivityTime).count() > 5)
        {
            engine.removeEntity(clients[i].entity);
        }
    }
}

void Rtype::run()
{
    while (engine.isOpen())
    {
        moveBackground(); // necessary for collision
        engine.update();
        checkInactivesClients();
    }
    std::cout << "engine closed!" << std::endl;
}

// factory to create component
//     Component *Factory::createComponent(std::string type, std::array<uint8_t, 128> data)

void Rtype::sendToClient(ClientInfo &client, network::datagram<protocol::data> content)
{
    // TODO : send to client
}

void Rtype::createPlayer(ClientInfo &client)
{
    // TODO : create a new player
    Haze::Entity *newPlayer = engine.createEntity();
    Haze::Velocity *velocityPlayer = new Haze::Velocity(0, 0);

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

    newPlayer->addComponent(velocityPlayer);
    newPlayer->addComponent(new Haze::Position(100, 200));
    newPlayer->addComponent(new Haze::Scale(3, 3));
    // newPlayer->addComponent(spaceshipSprite);
    // newPlayer->addComponent(new Haze::Animation({{100, 0, 33, 18},
    //                                                        {133, 0, 33, 18},
    //                                                        {166, 0, 33, 18},
    //                                                        {199, 0, 33, 18},
    //                                                        {232, 0, 33, 18}},
    //                                                       Haze::Animation::AnimationType::BOOMERANG, true, 0.2));
    newPlayer->addComponent(new Haze::Hitbox({{0, 0, 32, 14}}));
    newPlayer->addComponent(new Haze::HitboxDisplay());
    newPlayer->addComponent(new Haze::Collision("player", infos));
    newPlayer->addComponent(new Haze::OnKeyPressed(
        [this, &newPlayer](int i, std::vector<Haze::InputType> components)
        {
            if (std::find(components.begin(), components.end(), Haze::InputType::KEY_ENTER_INPUT) != components.end())
            {
                Haze::Entity *newShot = engine.createEntity();
                auto position = static_cast<Haze::Position *>(newPlayer->getComponent("Position"));
                newShot->addComponent(new Haze::Position(position->x + 33 * 3, position->y));
                newShot->addComponent(new Haze::Velocity(2, 0));
                newShot->addComponent(static_cast<Haze::Sprite *>(entities[SHOT]->getComponent("Sprite")));
                // newShot->addComponent(new Haze::Animation({{0, 0, 16, 14},
                //                                            {16, 0, 16, 14},
                //                                            {32, 0, 16, 14}},
                //                                           Haze::Animation::AnimationType::LOOP, true, 0.2));
            }

            auto velocity = static_cast<Haze::Velocity *>(newPlayer->getComponent("Velocity"));
            if (velocity == nullptr)
                newPlayer->addComponent(new Haze::Velocity(0, 0));
            velocity->x = 0;
            velocity->y = 0;

            if (std::find(components.begin(), components.end(), Haze::InputType::KEY_UP_ARROW) != components.end())
            {
                velocity->y += -5;
            }
            if (std::find(components.begin(), components.end(), Haze::InputType::KEY_LEFT_ARROW) != components.end())
            {
                velocity->x += -5;
            }
            if (std::find(components.begin(), components.end(), Haze::InputType::KEY_DOWN_ARROW) != components.end())
            {
                velocity->y += 5;
            }
            if (std::find(components.begin(), components.end(), Haze::InputType::KEY_RIGHT_ARROW) != components.end())
            {
                velocity->x += 5;
            }
        }));
    client.entity = newPlayer;
}

void Rtype::onReceive(udp::endpoint from, network::datagram<protocol::data> content)
{
    std::cout << "onReceive" << std::endl;
    // | ID            | Body         | Response ID    |
    // | ------------- | ------------ | -------------- |
    // | INPUT         | info_inputs  | NONE           |
    // | GET_ENTITY    | id_entity    | INFO_ENTITY    |
    // | GET_ENTITIES  | NONE         | INFO_ENTITIES  |
    // | GET_COMPONENT | id_component | INFO_COMPONENT |
    // | ALIVE         | NONE         | NONE           |

    // TODO : join & cie

    int8_t id_player = -1;
    switch (content.header.id)
    {
    case protocol::data::join:
    {
        bool exist = 0;
        for (int i = 0; i < 4; i++)
        {
            // * if the client already exist, and if he is not dead
            if (clients[i].endpoint == from && clients[i].entity != nullptr)
            {
                clients[i].lastActivityTime = std::chrono::high_resolution_clock::now();
                id_player = i;
                break;
            }
            // * if the client already exist, but if he is dead
            else if (clients[i].endpoint == from)
            {
                clients[i].lastActivityTime = std::chrono::high_resolution_clock::now();
                createPlayer(clients[i]);
                id_player = i;
                break;
            }
            // * if the client doesn't exist
            else if (std::chrono::duration<double>(std::chrono::high_resolution_clock::now() - clients[i].lastActivityTime).count() > 5)
            {
                clients[i].lastActivityTime = std::chrono::high_resolution_clock::now();
                clients[i].endpoint = from;
                createPlayer(clients[i]);
                id_player = i;
                break;
            }
        }
        // * if the server is full
        if (id_player == -1)
            return;
        break;
    }

    // ! use id_player
    case protocol::data::input: // TODO : could be many players, see about that
    {
        Haze::info_inputs_weak info;
        std::memcpy(&info, content.body.data(), content.header.size);
        Haze::info_inputs inputs;
        inputs.inputsPressed = std::vector<Haze::InputType>(info.pressedInputs.begin(), info.pressedInputs.end());
        inputs.inputsReleased = std::vector<Haze::InputType>(info.releasedInputs.begin(), info.releasedInputs.end());
        inputs.mouseType = info.mouseType;
        inputs.x = info.x;
        inputs.y = info.y;

        // clientData data = playersId[from];
        int id = -1;
        for (ClientInfo &data : clients)
            if (data.endpoint == from)
                id = data.id;

        engine.setInfoInputs(inputs, id); // TODO

        break;
    }
    case protocol::data::get_entity:
    {
        Haze::id_entity info;
        std::memcpy(&info, content.body.data(), content.header.size);
        // entities.push_back(engine.createEntity());
        // tell to every client to create an entity, with the id of the entity
        break;
    }
    case protocol::data::get_entities:
    {
        // tell to every client to delete an entity, with the id of the entity
        break;
    }
    case protocol::data::get_component:
    {
        Haze::id_component info;
        std::memcpy(&info, content.body.data(), content.header.size);
        // addComponent();
        break;
    }
    case protocol::data::alive:
    {
        // TODO
        break;
    }
    default:
        break;
    }
}

/*

write this when sending to a client

case protocol::data::create_entity:

    Haze::info_entity info;
    // cast content.body to info_entity
    std::memcpy(&info, content.body.data(), content.header.size);

    entities.push_back(engine.createEntity());


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
*/