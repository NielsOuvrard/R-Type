//
// Created by erwan on 10/11/23.
//

#include "server.h"

using namespace protocol;

server::server(uint16_t port)
    : server_interface(port)
{}

void server::onMessage(std::shared_ptr<network::connection<lobby>> from, network::message<lobby> &msg)
{
    switch (msg.header.id) {
        case lobby::start_room: {
            if (!_game) {
                _game = std::make_unique<Rtype>(_context);
                network::message<lobby> res(lobby::data_channel);
                res << _game->getEndpoint();
                this->messageAllClient(res);
                _game->start();
            }
            break;
        }

        default: {
            break;
        }
    }
}

bool server::onClientConnection(std::shared_ptr<network::connection<lobby>> client)
{
    return true;
}
