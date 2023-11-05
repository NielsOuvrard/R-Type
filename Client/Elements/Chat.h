//
// Created by erwan on 10/28/23.
//

#pragma once

#include "Element.h"
#include <list>

class Chat : public Element {
public:
    struct Message {
        std::string sender;
        std::string content;
    };

public:
    explicit Chat(Haze::Engine &engine);
    void build() override;
    void update() override;
    std::list<Message> _history;
};
