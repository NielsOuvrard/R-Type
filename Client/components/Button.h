//
// Created by erwan on 10/9/23.
//

#pragma once

#include "Engine.hpp"
#include "haze-core.hpp"
#include "haze-graphics.hpp"

namespace cmp {
    class Button {
    public:
        Button(Haze::Engine &engine, std::string label, std::function<void(int)> callback = {});
        void onClick(std::function<void(int)> callback) {
            auto prop = dynamic_cast<Haze::OnMouseReleased *>(_entity->getComponent("OnMouseReleased"));
            prop->callback = std::move(callback);
        }
        void setLabel(std::string label) { _label = std::move(label); }
        [[nodiscard]] Haze::Entity &getEntity() const;

    private:
        Haze::Engine &_engine;
        Haze::Entity *_entity;
        std::string _label;
    };
}// namespace cmp
