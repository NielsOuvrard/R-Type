//
// Created by erwan on 10/24/23.
//

#include "LobbyList.h"
#include "../Elements/Button.h"
#include "../Elements/Image.h"
#include "../Elements/Text.h"

LobbyList::LobbyList(Haze::Engine &engine, uint32_t &currentLobby, std::function<void()> join, std::function<void()> create, std::function<void()> disconnect)
    : Element(engine), _currentLobby(currentLobby), _join(std::move(join)), _create(std::move(create)), _disconnect(std::move(disconnect)) {}

void LobbyList::build()
{
    _children["window"] = std::make_shared<Image>(_engine, "assets/sprites/window.png", AxisPair{10, 10}, AxisPair{0.535, 0.535});
    _children["window"]->build();

    _children["title"] = std::make_shared<Text>(_engine, "Choose a lobby", "NotoMono.ttf", Haze::Text::colorHaze::WHITE, AxisPair{130, 30});
    _children["title"]->build();

    _children["join_img"] = std::make_shared<Image>(_engine, "assets/sprites/next_btn.png", AxisPair{670, 484}, AxisPair{0.48, 0.48});
    _children["join_img"]->build();
    _children["join"] = std::make_shared<Button>(
            _engine, [this](int) { _join(); }, AxisPair{670, 480});
    _children["join"]->build();
    _children["join"]->rm("HitboxDisplay");
    get<Button>("join")->setHitbox(10, 10, 82, 82);

    _children["disconnect_img"] = std::make_shared<Image>(_engine, "assets/sprites/close_btn.png", AxisPair{550, 484}, AxisPair{0.48, 0.48});
    _children["disconnect_img"]->build();
    _children["disconnect"] = std::make_shared<Button>(
            _engine, [this](int) { _disconnect(); }, AxisPair{550, 480});
    _children["disconnect"]->build();
    _children["disconnect"]->rm("HitboxDisplay");
    get<Button>("disconnect")->setHitbox(10, 10, 82, 82);

    _children["create_img"] = std::make_shared<Image>(_engine, "assets/sprites/new_btn.png", AxisPair{430, 25}, AxisPair{0.27, 0.27});
    _children["create_img"]->build();
    _children["create"] = std::make_shared<Button>(
            _engine, [this](int) { _create(); }, AxisPair{430, 25});
    _children["create"]->build();
    _children["create"]->rm("HitboxDisplay");
    get<Button>("create")->setHitbox(6, 6, 43, 43);
}

void LobbyList::update()
{
    Element::update();
    float offset = 100;
    float curr_offset = 0;
    for (auto &[id, item]: _items) {
        if (id == _currentLobby) {
            item->get<Image>("btn_img")->add(new Haze::Sprite("assets/sprites/list_item_selected.png"));
        } else {
            item->get<Image>("btn_img")->add(new Haze::Sprite("assets/sprites/list_item.png"));
        }
        item->update();
        item->setHide(false);
        item->setY(115 + curr_offset);
        curr_offset += offset;
    }
}

void LobbyList::setHide(bool state)
{
    Element::setHide(state);
    for (auto &[id, item]: _items) {
        item->setHide(true);
    }
}
