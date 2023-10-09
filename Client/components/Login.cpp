//
// Created by erwan on 10/9/23.
//

#include "Login.h"

namespace cmp {
    Login::Login(
            Haze::Engine &engine, float x, float y, std::function<void(const std::string &, uint16_t)> callback)
        : _engine(engine),
          _ip(_engine, "address"),
          _port(_engine, "port"),
          _validate(_engine, "connect"),
          _position({x, y}),
          _onValidateFnc(std::move(callback)) {
        setPosition(_position.x, _position.y);

        _validate.onClick([this](int id) {
            _onValidateFnc(_ip.getValue(), std::stoi(_port.getValue()));
        });
    }
    void Login::setPosition(float x, float y) {
        auto ip_pos = dynamic_cast<Haze::Position *>(_ip.getEntity().getComponent("Position"));
        auto port_pos = dynamic_cast<Haze::Position *>(_port.getEntity().getComponent("Position"));
        auto button_pos = dynamic_cast<Haze::Position *>(_validate.getEntity().getComponent("Position"));

        ip_pos->x = x;
        ip_pos->y = y;

        port_pos->x = x;
        port_pos->y = y + 100;

        button_pos->x = x;
        button_pos->y = y + 200;
    }
    void Login::onValidate(std::function<void(const std::string &, uint16_t)> callback) {
        _onValidateFnc = std::move(callback);
    }
    void Login::hide() {
        _ip.getEntity().addComponent(new Haze::Hide);
        _port.getEntity().addComponent(new Haze::Hide);
        _validate.getEntity().addComponent(new Haze::Hide);
    }
    void Login::unhide() {
        _ip.getEntity().removeComponent("Hide");
        _port.getEntity().removeComponent("Hide");
        _validate.getEntity().removeComponent("Hide");
    }
}// namespace cmp