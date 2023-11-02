//
// Created by erwan on 10/28/23.
//

#include "Lobby.h"
#include "../Elements/Chat.h"

Lobby::Lobby(Haze::Engine &engine) : Element(engine), players{UserCard(engine, -100, -100), UserCard(engine, -100, -100), UserCard(engine, -100, -100), UserCard(engine, -100, -100)} {}

void Lobby::update()
{
    Element::update();
    for (auto &user: players) {
        user.update();
    }
}

void Lobby::build()
{
    _children["chat"] = std::make_shared<Chat>(_engine);
    _children["chat"]->build();
    int i = 0;
    for (auto &player: players) {
        player.x = 520;
        player.y = 15 + 90 * i;
        player.build();
        i++;
    }
}
