//
// Created by erwan on 9/29/23.
//

#include "Room.h"
#include "Rtype.hpp"
#include "net_connection.h"
#include "net_data_channel.h"
#include "net_server.h"
#include "protocols.h"

class server : public network::server_interface<protocol::lobby> {
public:
    explicit server(uint16_t port);

protected:
    void onMessage(std::shared_ptr<network::connection<protocol::lobby>> from, network::message<protocol::lobby> &msg) override;
    bool onClientConnection(std::shared_ptr<network::connection<protocol::lobby>> client) override;
    void onClientDisconnect(std::shared_ptr<network::connection<protocol::lobby>> client) override;

private:
    uint32_t _roomCounter = 1;
    uint32_t _threadCounter = 1;
    std::map<uint32_t, std::unique_ptr<Room>> _rooms;
    std::map<uint32_t, std::thread> _threads;
};
