//
// Created by erwan on 10/23/23.
//

#include "Background.h"
#include "../Elements/Image.h"

Background::Background(Haze::Engine &engine) : Element(engine) {}

void Background::build()
{
    _children["bg1"] = std::make_shared<Image>(_engine, "assets/sprites/client_bg.png", AxisPair{0, 0}, AxisPair{0.74, 0.74});
    _children["bg1"]->build();
    _children["bg1"]->add(new Haze::Velocity(0.0, -100, 1));

    _children["bg2"] = std::make_shared<Image>(_engine, "assets/sprites/client_bg.png", AxisPair{0, 1080}, AxisPair{0.74, 0.74});
    _children["bg2"]->build();
    _children["bg2"]->add(new Haze::Velocity(0.0, -100, 1));
}

void Background::update()
{
    auto pos1 = _children["bg1"]->comp<Haze::Position>("Position");
    if (pos1->y <= -1080) {
        pos1->y = 1080;
    }
    auto pos2 = _children["bg2"]->comp<Haze::Position>("Position");
    if (pos2->y <= -1080) {
        pos2->y = 1080;
    }
}
