//
// Created by erwan on 10/28/23.
//

#include "Lobby.h"

#include "../Elements/Button.h"
#include "../Elements/Chat.h"
#include "../Elements/Image.h"
#include <utility>

Lobby::Lobby(Haze::Engine &engine, std::function<void()> onReady) : Element(engine), onReady(std::move(onReady)), players{UserCard(engine, -100, -100), UserCard(engine, -100, -100), UserCard(engine, -100, -100), UserCard(engine, -100, -100)} {}

void Lobby::update()
{
    Element::update();
    for (auto &user: players) {
        user.update();
    }
}

void Lobby::setHide(bool state)
{
    Element::setHide(state);
    for (auto &player: players) {
        player.setHide(true);
    }
}

void Lobby::build()
{
    _children["chat"] = std::make_shared<Chat>(_engine);
    _children["chat"]->build();
    _children["start_img"] = std::make_shared<Image>(_engine, "assets/sprites/start_btn.png", AxisPair{520, 500}, AxisPair{0.68, 0.68});
    _children["start_img"]->build();
    _children["start_btn"] = std::make_shared<Button>(
            _engine, [this](int) { onReady(); }, AxisPair{520, 500});
    _children["start_btn"]->build();
    get<Button>("start_btn")->setHitbox(8, 8, 260, 60);

    int i = 0;
    for (auto &player: players) {
        player.x = 520;
        player.y = 15 + 90 * i;
        player.build();
        i++;
    }
}
