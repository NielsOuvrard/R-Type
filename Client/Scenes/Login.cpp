//
// Created by erwan on 10/20/23.
//

#include "Login.h"
#include "../Elements/Button.h"
#include "../Elements/Image.h"

Login::Login(Haze::Engine &engine) : Element(engine) {}

void Login::build()
{
    _children["logo"] = std::make_shared<Image>(_engine, "assets/sprites/haze_logo.png", AxisPair{150.0, 40.0}, AxisPair{0.7, 0.7});
    _children["logo"]->build();

    _children["name_img"] = std::make_shared<Image>(_engine, "assets/sprites/button.png", AxisPair{210, 220}, AxisPair{1, 1});
    _children["name_img"]->build();
    _children["name"] = std::make_shared<TextInput>(_engine, "name", AxisPair{250, 220 + 25});
    _children["name"]->build();
    get<TextInput>("name")->setHitbox(-20, -20, 320, 81);

    _children["ip_img"] = std::make_shared<Image>(_engine, "assets/sprites/button.png", AxisPair{210, 345}, AxisPair{1, 1});
    _children["ip_img"]->build();
    _children["ip"] = std::make_shared<TextInput>(_engine, "ip", AxisPair{250, 345 + 25});
    _children["ip"]->build();
    get<TextInput>("ip")->setHitbox(-20, -20, 320, 81);

    _children["port_img"] = std::make_shared<Image>(_engine, "assets/sprites/button.png", AxisPair{210, 470}, AxisPair{1, 1});
    _children["port_img"]->build();
    _children["port"] = std::make_shared<TextInput>(_engine, "port", AxisPair{250, 470 + 25});
    _children["port"]->build();
    get<TextInput>("port")->setHitbox(-20, -20, 320, 81);


    _children["start_img"] = std::make_shared<Image>(_engine, "assets/sprites/play_btn.png", AxisPair{600, 424}, AxisPair{0.48, 0.48});
    _children["start_img"]->build();
    _children["start"] = std::make_shared<Button>(_engine, AxisPair{600, 420});
    _children["start"]->build();
    get<Button>("start")->setHitbox(10, 10, 82, 82);
}

void Login::update()
{
}
