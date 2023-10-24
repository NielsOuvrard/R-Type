//
// Created by erwan on 10/24/23.
//

#include "LobbyList.h"
#include "../Elements/Button.h"
#include "../Elements/Image.h"
#include "../Elements/Text.h"

LobbyList::LobbyList(Haze::Engine &engine, std::function<void(int)> join)
    : Element(engine), _join(std::move(join)) {}

void LobbyList::build()
{
    _children["window"] = std::make_shared<Image>(_engine, "assets/sprites/window.png", AxisPair{10, 10}, AxisPair{0.535, 0.535});
    _children["window"]->build();

    _children["title"] = std::make_shared<Text>(_engine, "Choose a lobby", "NotoMono.ttf", Haze::Text::colorHaze::WHITE, AxisPair{130, 30});
    _children["title"]->build();

    _children["join_img"] = std::make_shared<Image>(_engine, "assets/sprites/next_btn.png", AxisPair{670, 484}, AxisPair{0.48, 0.48});
    _children["join_img"]->build();
    _children["join"] = std::make_shared<Button>(_engine, _join, AxisPair{670, 480});
    _children["join"]->build();
    get<Button>("join")->setHitbox(10, 10, 82, 82);
}

void LobbyList::update()
{
}
