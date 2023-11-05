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

    _children["txt_img"] = std::make_shared<Image>(_engine, "assets/sprites/input.png", AxisPair{25, 510}, AxisPair{1, 1});
    _children["txt_img"]->build();

    _children["input"] = std::make_shared<TextInput>(_engine, "enter your message", AxisPair{38, 523}, AxisPair{0.6, 0.6});
    get<TextInput>("input")->limit = 40;
    _children["input"]->build();
    get<TextInput>("input")->setHitbox(-13, -13, 770, 70);
    get<TextInput>("input")->rm("HitboxDisplay");

    _children["txt"] = std::make_shared<Text>(_engine, "", "NotoMono.ttf", Haze::Text::colorHaze::WHITE, AxisPair{30, 100}, AxisPair{0.6, 0.6});
    _children["txt"]->build();
}

void Chat::update()
{
    static std::size_t diff = _history.size();
    if (diff != _history.size()) {
        auto txt = get<Text>("txt");
        std::stringstream ss;
        for (auto &chat: _history) {
            ss << chat.sender << ":";
            std::istringstream iss(chat.content);
            std::string word;
            std::size_t count = chat.sender.length() + 2;
            while (iss >> word) {
                std::cout << "Count: " << count << "Word : " << word << '\n';
                if (count + word.length() > 43) {
                    ss << '\n';
                    count = 0;
                }
                if (count > 0) {
                    ss << " ";
                    count++;
                }
                ss << word;
                count += word.length();
            }
            ss << '\n';
        }
        get<Text>("txt")->setValue(ss.str());
        std::string out = ss.str();
        size_t i = std::count(out.begin(), out.end(), '\n');
        while (i-- > 18) {
            _history.pop_front();
        }
    }
    diff = _history.size();
    Element::update();
}
