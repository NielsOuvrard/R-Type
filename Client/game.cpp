//
// Created by erwan on 10/10/23.
//

#include "game.h"

game::game(asio::io_context &context, Haze::Engine &engine)
    : network::data_channel<data>(context),
      _engine(engine)
{
}

void game::onReceive(udp::endpoint from, network::datagram<data> content)
{
    switch (content.header.id) {
        case data::add_component:
            Haze::info_component info;
            std::memcpy(&info, content.body.data(), content.header.size);
            addComponent();
            break;
    }
}
