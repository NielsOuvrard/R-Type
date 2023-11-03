//
// Created by erwan on 10/25/23.
//

#include "LobbyItem.h"
#include "../Elements/Image.h"
#include <sstream>

void LobbyItem::update()
{
    Element::update();
    std::stringstream ss;
    ss << "#" << _id << " - ";
    if (_nbLeft != _nbRight) {
        ss << _nbLeft << "/" << _nbRight;
    } else {
        ss << "FULL";
    }

    get<Button>("btn")->setLabel(ss.str());
}

void LobbyItem::build()
{
    _children["btn_img"] = std::make_shared<Image>(_engine, "assets/sprites/list_item.png", AxisPair{40, 300}, AxisPair{1, 1});
    _children["btn_img"]->build();
    _children["btn"] = std::make_shared<Button>(
            _engine, [this](int) {
                std::cout << "Click Lobby #" << _id << std::endl;
                _selectLobby(_id);
            },
            AxisPair{80, 300});
    _children["btn"]->build();
    get<Button>("btn")->setHitbox(-25, -20, 420, 80);
    get<Button>("btn")->rm("HitboxDisplay");
}

LobbyItem::LobbyItem(Haze::Engine &engine, int id, int nbRight, int nbLeft, std::function<void(uint32_t)> selectLobby)
    : Element(engine), _id(id), _nbRight(nbRight), _nbLeft(nbLeft), _selectLobby(std::move(selectLobby)) {}

void LobbyItem::setX(float x)
{
    auto p = dynamic_cast<Haze::Position *>(get<Button>("btn")->getEntity().getComponent("Position"));
    p->x = x;
    p = dynamic_cast<Haze::Position *>(get<Image>("btn_img")->getEntity().getComponent("Position"));
    p->x = x;
}

void LobbyItem::setY(float y)
{
    auto p = dynamic_cast<Haze::Position *>(get<Button>("btn")->getEntity().getComponent("Position"));
    p->y = 25 + y;
    p = dynamic_cast<Haze::Position *>(get<Image>("btn_img")->getEntity().getComponent("Position"));
    p->y = y;
}
