//
// Created by erwan on 10/9/23.
//

#pragma once

#include "haze-core.hpp"
#include "haze-graphics.hpp"

#include "Button.h"
#include "TextInput.h"

namespace element {
    class Login {
    public:
        Login(Haze::Engine &engine, float x, float y, std::function<void(const std::string &, uint16_t)> callback);

    public:
        void onValidate(std::function<void(const std::string &, uint16_t)> callback);

    public:
        void setPosition(float x, float y);
        void setHide(bool state);

        [[nodiscard]] bool isHidden() const { return _hidden; }

    private:
        Haze::Engine &_engine;
        struct {
            float x;
            float y;
        } _position;

        std::function<void(const std::string &, uint16_t)> _onValidateFnc = [](const std::string &ip, uint16_t port) {
            std::cout << "Ip: " << ip << ":" << port << std::endl;
        };

        TextInput _ip;
        TextInput _port;
        Button _validate;

        bool _hidden = false;
    };
}// namespace element
