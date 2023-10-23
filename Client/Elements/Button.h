//
// Created by erwan on 10/9/23.
//

#pragma once

#include "Element.h"
#include "Engine.hpp"
#include "haze-core.hpp"
#include "haze-graphics.hpp"

//namespace element {
//    class Button {
//    public:
//        Button(Haze::Engine &engine, std::string label, std::function<void(int)> callback = {});
//        void onClick(std::function<void(int)> callback) {
//            auto prop = dynamic_cast<Haze::OnMouseReleased *>(_entity->getComponent("OnMouseReleased"));
//            prop->callback = std::move(callback);
//        }
//        void setLabel(std::string label) { _label = std::move(label); }
//        [[nodiscard]] Haze::Entity &getEntity() const;
//
//    private:
//        Haze::Engine &_engine;
//        Haze::Entity *_entity;
//        std::string _label;
//    };
//}// namespace element

class Button : public Element {
public:
    explicit Button(Haze::Engine &engine, AxisPair position = {0, 0}, AxisPair scale = {1, 1});
    void update() override;
    void build() override;
    void setLabel(std::string label);
    void setHitbox(int x, int y, int width, int height);

private:
    std::string _label;
    std::string _fontFile = "NotoMono.ttf";
    Haze::Text::colorHaze _fontColor = Haze::Text::WHITE;
};
