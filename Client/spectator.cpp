//
// Created by erwan on 10/10/23.
//

#include "spectator.h"

spectator::spectator(asio::io_context &context, Haze::Engine &engine)
    : network::data_channel<data>(context),
      _engine(engine),
      _inputGrabber(_engine.createEntity())
{
    _inputGrabber->addComponent(new Haze::OnKeyPressed([this](int id, std::vector<Haze::InputType> keys) {
        auto win = dynamic_cast<Haze::Window *>(_engine.getComponentList()->getComponent("Window", 0));
        if (!win || !win->active) return;
        Haze::info_inputs_weak info{};
        uint32_t i = 0;
        for (auto &key: keys) {
            if (i < info.pressedInputs.max_size()) {
                info.pressedInputs[i] = key;
                i++;
            }
        }
        if (i) {
            network::datagram<data> msg(data::input);
            std::memcpy(msg.body.data(), &info, sizeof(Haze::info_inputs_weak));
            msg.header.size = sizeof(Haze::info_inputs_weak);
            sendAll(msg);
            aliveCD.Activate();
        }
    }));
    _inputGrabber->addComponent(new Haze::OnKeyReleased([this](int id, std::vector<Haze::InputType> keys) {
        uint32_t i = 0;
        Haze::info_inputs_weak info{};
        for (auto &key: keys) {
            if (i < info.releasedInputs.max_size()) {
                info.releasedInputs[i] = key;
                i++;
            }
        }
        if (i) {
            network::datagram<data> msg(data::input);
            std::memcpy(msg.body.data(), &info, sizeof(Haze::info_inputs_weak));
            msg.header.size = sizeof(Haze::info_inputs_weak);
            sendAll(msg);
        }
    }));
}

void spectator::onReceive(udp::endpoint from, network::datagram<data> content)
{
    switch (content.header.id) {
        case data::create_entity: {
            Haze::entity_id id = {0};
            std::memcpy(&id, content.body.data(), content.header.size);
            std::cout << "[" << id.id << "] Created\n";
            createEntity(id);
            break;
        }
        case data::delete_entity: {
            Haze::entity_id id = {0};
            std::memcpy(&id, content.body.data(), content.header.size);
            std::cout << "[" << id.id << "] Deleted\n";
            deleteEntity(id);
            break;
        }
        case data::add_component: {
            Haze::component_info info = {0};
            std::memcpy(&info, content.body.data(), content.header.size);
            std::cout << "[" << info.id << "] " << info.name << " added\n";
            addComponent(info);
            break;
        }
        case data::remove_component: {
            std::cout << "[GAME] removing component\n";
            Haze::component_id info = {0};
            std::memcpy(&info, content.body.data(), content.header.size);
            std::cout << "[" << info.id << "] " << info.name << " removed\n";
            removeComponent(info);
            break;
        }
        default:
            std::cout << "[GAME] Error couldn't parse datagram";
            break;
    }
}

void spectator::createEntity(Haze::entity_id info)
{
    _entities.insert({
            info.id,
            _engine.createEntity(),
    });
}

void spectator::deleteEntity(Haze::entity_id info)
{
    _entities[info.id]->addComponent(new Haze::Destroy);
    _entities.erase(info.id);
}

void spectator::addComponent(Haze::component_info info)
{
    // * if didn't exist
    if (_entities.find(info.id) == _entities.end()) {
        _entities.insert({
                info.id,
                _engine.createEntity(),
        });
    }
    Haze::Component *comp = Haze::Factory::createComponent(std::string(info.name), info.data);
    if (!comp) {
        std::cout << "\033[31m[GAME] Error: couldn't create component " << info.name << "\033[0m\n";
        return;
    }
    if (comp->getType() == "Position") {
        Haze::Interpolation *interpolation = dynamic_cast<Haze::Interpolation *>(_entities[info.id]->getComponent("Interpolation"));
        if (interpolation == nullptr) {
            _entities[info.id]->addComponent(comp);
            return;
        }
        Haze::Position *pos = dynamic_cast<Haze::Position *>(_entities[info.id]->getComponent("Position"));
        Haze::PositionInterpolation *PosI = dynamic_cast<Haze::PositionInterpolation *>(_entities[info.id]->getComponent("PositionInterpolation"));
        Haze::Position *newPos = dynamic_cast<Haze::Position *>(comp);

        if (pos == nullptr || PosI == nullptr) {
            if (pos == nullptr)
                _entities[info.id]->addComponent(comp);
            if (PosI == nullptr)
                _entities[info.id]->addComponent(new Haze::PositionInterpolation(newPos->x, newPos->y, newPos->x, newPos->y));
        } else {
            pos->x = PosI->nextX;
            pos->y = PosI->nextY;
            PosI->prevX = PosI->nextX;
            PosI->prevY = PosI->nextY;
            PosI->nextX = newPos->x;
            PosI->nextY = newPos->y;
            _entities[info.id]->addComponent(new Haze::VelocityInterpolation(PosI->nextX - PosI->prevX, PosI->nextY - PosI->prevY, 1.0f / interpolation->framerate));
        }
    } else {
        _entities[info.id]->addComponent(comp);
    }
}

void spectator::removeComponent(Haze::component_id info)
{
    _entities[info.id]->removeComponent(info.name);
}
