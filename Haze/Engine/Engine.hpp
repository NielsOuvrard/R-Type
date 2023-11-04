/*
** EPITECH PROJECT, 2023
** B-CPP-500-MAR-5-1-rtype-erwan.gonzales
** File description:
** Engine
*/

#pragma once
#include "ComponentList.hpp"
#include "Entity.hpp"
#include "IPipeline.hpp"
#include "protocol.hpp"
#include <chrono>
#include <iostream>
#include <map>
#include <memory>
#include <mutex>
#include <thread>
#include <vector>

namespace Haze {
    class Engine {
    public:
        Engine(int framerate, int lib = 0);
        ~Engine();
        void init();
        void update();
        Entity *createEntity();
        Entity *getEntity(size_t id);
        void removeEntity(size_t id);
        void removeEntity(Entity *entity);
        bool isOpen();
        void setInfoInputs(info_inputs info, size_t id);

        int getFramerate() { return _framerate; }

        ComponentList *getComponentList() { return _componentList; }

        std::vector<info_inputs> *getInfoInputs() { return &_infoInputs; }

    protected:
    private:
        std::vector<std::unique_ptr<Entity>> _entities;
        std::vector<std::unique_ptr<IPipeline>> _pipelines;
        ComponentList *_componentList;
        std::vector<info_inputs> _infoInputs;
        int _framerate = 60;
        std::chrono::time_point<std::chrono::system_clock> _lastTime;
    };

    void ticThread(Haze::Engine *engine);
}// namespace Haze
