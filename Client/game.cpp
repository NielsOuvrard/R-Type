//
// Created by erwan on 10/10/23.
//

#include "game.h"

game::game(asio::io_context &context, Haze::Engine &engine)
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

void game::onReceive(udp::endpoint from, network::datagram<data> content)
{
    switch (content.header.id) {
        case data::create_entity: {
            //std::cout << "[GAME] creating entity\n";
            Haze::entity_id id = {0};
            std::memcpy(&id, content.body.data(), content.header.size);
            createEntity(id);
            std::cout << "create entity " << id.id << std::endl;
            break;
        }
        case data::delete_entity: {
            //std::cout << "[GAME] deleting entity\n";
            Haze::entity_id id = {0};
            std::memcpy(&id, content.body.data(), content.header.size);
            deleteEntity(id);
            break;
        }
        case data::add_component: {
            //std::cout << "[GAME] adding component\n";
            Haze::component_info info = {0};
            std::memcpy(&info, content.body.data(), content.header.size);
            addComponent(info);
            break;
        }
        case data::remove_component: {
            //std::cout << "[GAME] removing component\n";
            Haze::component_id info = {0};
            std::memcpy(&info, content.body.data(), content.header.size);
            removeComponent(info);
            break;
        }
        default:
            std::cout << "[GAME] Error couldn't parse datagram";
            break;
    }
}

void game::createEntity(Haze::entity_id id)
{
    _entities.insert({
            id.id,
            _engine.createEntity(),
    });
}

void game::deleteEntity(Haze::entity_id id)
{
    _engine.removeEntity(id.id);
    _entities.erase(id.id);
}

void game::addComponent(Haze::component_info info)
{
    _entities[info.id]->addComponent(Haze::Factory::createComponent(std::string(info.name), info.data));
}

void game::removeComponent(Haze::component_id id)
{
    _entities[id.id]->removeComponent(id.name);
}
