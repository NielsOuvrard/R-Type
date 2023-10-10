//
// Created by erwan on 10/10/23.
//

#pragma once

#include "haze-core.hpp"
#include "haze-graphics.hpp"
#include <list>

namespace element {
    class Element {
    public:
        Element(Haze::Engine &engine) : _engine(engine) {}
        virtual ~Element() = default;

    public:
        void setOrigin(float ox, float oy) {
            _ox = ox;
            _oy = oy;
            if (_entity) {
                auto cmp = dynamic_cast<Haze::Position *>(_entity->getComponent("Position"));
                cmp->y = _oy + _y;
                cmp->x = _ox + _x;
            }
            for (auto &child: _children) {
                child->setOrigin(ox, oy);
            }
        }

        void setPosition(float x, float y) {
            _x = x;
            _y = y;
            if (_entity) {
                auto cmp = dynamic_cast<Haze::Position *>(_entity->getComponent("Position"));
                cmp->y = _oy + _y;
                cmp->x = _ox + _x;
            }
            for (auto &child: _children) {
                child->setPosition(x, y);
            }
        }

        void setHide(bool state) {
            _isHidden = state;
            if (_entity) {
                if (state) {
                    _entity->addComponent(new Haze::Hide);
                } else {
                    _entity->removeComponent("Hide");
                }
            }
            for (auto &child: _children) {
                child->setHide(state);
            }
        }

    public:
        bool isHidden() {
            return _isHidden;
        }

    protected:
        Haze::Engine &_engine;
        Haze::Entity *_entity = nullptr;
        bool _isHidden = false;
        float _x, _y, _ox, _oy;

        std::list<std::unique_ptr<Element>> _children;
    };
}// namespace element
