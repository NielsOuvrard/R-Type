//
// Created by erwan on 10/28/23.
//

#include "Chat.h"
#include "Image.h"
#include "Text.h"
#include "TextInput.h"

Chat::Chat(Haze::Engine &engine) : Element(engine) {}

void Chat::build()
{
    _children["window"] = std::make_shared<Image>(_engine, "assets/sprites/window.png", AxisPair{10, 10}, AxisPair{0.535, 0.535});
    _children["window"]->build();

    _children["title"] = std::make_shared<Text>(_engine, "Chat", "NotoMono.ttf", Haze::Text::colorHaze::WHITE, AxisPair{150, 30});
    _children["title"]->build();

    _children["input"] = std::make_shared<TextInput>(_engine, "enter your message", AxisPair{30, 500}, AxisPair{0.6, 0.6});
    get<TextInput>("input")->limit = 40;
    _children["input"]->build();

    _children["txt"] = std::make_shared<Text>(_engine, "", "NotoMono.ttf", Haze::Text::colorHaze::WHITE, AxisPair{50, 100}, AxisPair{0.6, 0.6});
    _children["txt"]->build();
}

void Chat::update()
{
    static std::size_t diff = _history.size();
    if (diff != _history.size()) {
        auto txt = get<Text>("txt");
        std::stringstream ss;
        int i = 0;
        for (auto &chat: _history) {
            if (i++ == 10) {
                break;
            }

            ss << "[" << chat.sender << "]: " << chat.content << std::endl;
        }
        get<Text>("txt")->setValue(ss.str());
    }
    diff = _history.size();
    Element::update();
}
