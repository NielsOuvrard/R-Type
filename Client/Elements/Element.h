//
// Created by erwan on 10/10/23.
//

#pragma once

#include "haze-core.hpp"
#include "haze-graphics.hpp"
#include <stack>

class Element {
public:
    using Node = std::map<std::string, std::shared_ptr<Element>>;

    struct AxisPair {
        float x;
        float y;
    };

public:
    explicit Element(Haze::Engine &engine) : _engine(engine), _position{0, 0}, _scale{1, 1} {}

    virtual ~Element() = default;

    virtual void build() = 0;

    virtual void update()
    {
        for (auto &[name, child]: _children) {
            child->update();
        }
    }

public:
    template<typename T>
    std::shared_ptr<T> get(const std::string &idx)
    {
        return std::dynamic_pointer_cast<T>(_children[idx]);
    };

    [[nodiscard]] bool getHide() { return _hide; }

    virtual void setHide(bool state = true)
    {
        _hide = state;
        if (_entity) {
            if (state) {
                _entity->addComponent(new Haze::Hide);
            } else {
                _entity->removeComponent("Hide");
            }
        }

        std::stack<Node::iterator> nodeStack;
        for (auto child = _children.begin(); child != _children.end(); ++child) {
            nodeStack.push(child);
        }

        while (!nodeStack.empty()) {
            auto current = nodeStack.top();
            nodeStack.pop();

            if (current->second->_entity) {
                if (state) {
                    current->second->_entity->addComponent(new Haze::Hide);
                } else {
                    current->second->_entity->removeComponent("Hide");
                }
            }

            for (auto child = current->second->_children.begin(); child != current->second->_children.end(); ++child) {
                nodeStack.push(child);
            }
        }
    }

    void add(Haze::Component *component)
    {
        _entity->addComponent(component);
    }

    void rm(const std::string &type)
    {
        _entity->removeComponent(type);
    }

    template<typename T>
    T *comp(const std::string &type)
    {
        return dynamic_cast<T *>(_entity->getComponent(type));
    }

    Haze::Entity &getEntity() { return *_entity; }

protected:
    void buildEntity()
    {
        _entity = _engine.createEntity();
        _entity->addComponent(new Haze::Position(_position.x, _position.y));
        _entity->addComponent(new Haze::Scale(_scale.x, _scale.y));
    }

protected:
    Haze::Engine &_engine;
    Haze::Entity *_entity = nullptr;

    bool _hide = false;
    AxisPair _position;
    AxisPair _scale;
    std::string _id;
    Node _children;
};
