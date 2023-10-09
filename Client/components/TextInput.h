//
// Created by erwan on 10/8/23.
//

#pragma once

#include "Engine.hpp"
#include "haze-core.hpp"
#include "haze-graphics.hpp"

namespace cmp {
    class TextInput {
    public:
        explicit TextInput(Haze::Engine &engine, std::string placeHolder);
        [[nodiscard]] Haze::Entity &getEntity() const;
        [[nodiscard]] const std::string &getValue() const;
        void setFocus(bool isFocused);

    private:
        Haze::Engine &_engine;
        Haze::Entity *_entity;

        bool _isFocused = false;
        std::string _placeHolder;
        std::string _value;
    };
}// namespace cmp
