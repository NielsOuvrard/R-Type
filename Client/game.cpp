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
        uint32_t i = 0;
        Haze::info_inputs_weak info{};
        for (auto &key: keys) {
            if (i < info.pressedInputs.max_size()) {
                info.pressedInputs[0] = key;
                i++;
            }
        }
        if (i) {
            network::datagram<data> msg(data::input);
            std::memcpy(msg.body.data(), &info, sizeof(Haze::info_inputs_weak));
            sendAll(msg);
        }
    }));
}

void game::onReceive(udp::endpoint from, network::datagram<data> content)
{
    switch (content.header.id) {
        case data::create_entity: {
            Haze::entity_id id = {0};
            std::memcpy(&id, content.body.data(), content.header.size);
            createEntity(id);
            break;
        }
        case data::delete_entity: {
            Haze::entity_id id = {0};
            std::memcpy(&id, content.body.data(), content.header.size);
            deleteEntity(id);
            break;
        }
        case data::add_component: {
            Haze::component_info info = {0};
            std::memcpy(&info, content.body.data(), content.header.size);
            addComponent(info);
            break;
        }
        case data::remove_component: {
            Haze::component_id info = {0};
            std::memcpy(&info, content.body.data(), content.header.size);
            removeComponent(info);
            break;
        }
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
    Haze::Entity *e = _engine.getEntity(info.id);
    e->addComponent(Haze::Factory::createComponent(info.name, info.data));
}

void game::removeComponent(Haze::component_id id)
{
    _entities[id.id]->removeComponent(id.name);
}
