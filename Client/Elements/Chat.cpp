//
// Created by erwan on 10/28/23.
//

#include "Chat.h"
#include "Image.h"
#include "Text.h"

Chat::Chat(Haze::Engine &engine) : Element(engine) {}

void Chat::build()
{
    _children["window"] = std::make_shared<Image>(_engine, "assets/sprites/window.png", AxisPair{10, 10}, AxisPair{0.535, 0.535});
    _children["window"]->build();

    _children["title"] = std::make_shared<Text>(_engine, "Chat", "NotoMono.ttf", Haze::Text::colorHaze::WHITE, AxisPair{150, 30});
    _children["title"]->build();
}

void Chat::update()
{
    Element::update();
}
