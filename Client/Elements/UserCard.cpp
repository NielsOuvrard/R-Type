//
// Created by erwan on 10/31/23.
//

#include "UserCard.h"
#include "Button.h"
#include "Image.h"
#include "Text.h"

void UserCard::build()
{
    _children["img"] = std::make_shared<Image>(_engine, "assets/sprites/table2.png", AxisPair{-100, -100}, AxisPair{0.5, 0.5});
    _children["img"]->build();

    _children["avatar"] = std::make_shared<Image>(_engine, "assets/sprites/usericon.png", AxisPair{-100, -100}, AxisPair{0.3, 0.3});
    _children["avatar"]->build();

    _children["star"] = std::make_shared<Image>(_engine, "assets/sprites/star.png", AxisPair{-100, -100}, AxisPair{0.10, 0.10});
    _children["star"]->build();
    if (!owner) { _children["star"]->setHide(true); }

    _children["kick_img"] = std::make_shared<Image>(_engine, "assets/sprites/close_btn.png", AxisPair{-100, -100}, AxisPair{0.3, 0.3});
    _children["kick_img"]->build();
    _children["kick_btn"] = std::make_shared<Button>(
            _engine, [this](int) { onKick(name); }, AxisPair{-100, -100}, AxisPair{1, 1});
    _children["kick_btn"]->build();
    get<Button>("kick_btn")->setHitbox(7, 5, 50, 50);
    _children["kick_btn"]->rm("HitboxDisplay");

    _children["name"] = std::make_shared<Text>(_engine, name, "NotoMono.ttf", Haze::Text::colorHaze::WHITE, AxisPair{-100, -100}, AxisPair{1, 1});
    _children["name"]->build();
}

void UserCard::update()
{
    Element::update();
    _children["img"]->add(new Haze::Position(x, y));
    _children["avatar"]->add(new Haze::Position(avatar.x + x, avatar.y + y));
    _children["star"]->add(new Haze::Position(star.x + x, star.y + y));
    _children["star"]->setHide(!owner);
    _children["kick_img"]->add(new Haze::Position(kick_img.x + x, kick_img.y + y));
    _children["kick_btn"]->add(new Haze::Position(kick_btn.x + x, kick_btn.y + y));
    _children["name"]->add(new Haze::Position(txt.x + x, txt.y + y));
    get<Text>("name")->setValue(name);
    if (ready) {
        get<Image>("img")->add(new Haze::Sprite("assets/sprites/table2_gold.png"));
    } else {
        get<Image>("img")->add(new Haze::Sprite("assets/sprites/table2.png"));
    }
}

void UserCard::setHide(bool state)
{
    Element::setHide(state);
}

UserCard::UserCard(Haze::Engine &engine, int x, int y) : Element(engine), x(x), y(y) {}
