//
// Created by erwan on 9/29/23.
//

#include "Rtype.hpp"
#include "data.h"
#include "lobby.h"
#include "net_connection.h"
#include "net_data_channel.h"
#include "net_server.h"

class server : public network::server_interface<protocol::lobby> {
public:
    explicit server(uint16_t port);

protected:
    void onMessage(std::shared_ptr<network::connection<protocol::lobby>> from, network::message<protocol::lobby> &msg) override;
    bool onClientConnection(std::shared_ptr<network::connection<protocol::lobby>> client) override;

private:
    std::unique_ptr<Rtype> _game = nullptr;
};
