//
// Created by erwan on 9/29/23.
//

// #include "common.h"
#include "data.h"
#include "lobby.h"
#include "net_connection.h"
#include "net_data_channel.h"
#include "net_server.h"
#include "Rtype.hpp"

class server : public network::server_interface<protocol::Lobby> {
public:
    explicit server(uint16_t port) : network::server_interface<protocol::Lobby>(port) {}

protected:
    void onMessage(std::shared_ptr<network::connection<protocol::Lobby>> from, network::message<protocol::Lobby> &msg) override {
        switch (msg.header.id) {
            case protocol::Lobby::start_room:
                if (!_dataChannel) {
                    _dataChannel = std::make_shared<network::data_channel<protocol::UDPProtocol>>(this->_context);
                    network::message<protocol::Lobby> res = {{protocol::Lobby::data_channel, 0}};
                    res << _dataChannel->getEndpoint();
                    this->messageAllClient(res);
                    Rtype rtype;
                    rtype.run(_dataChannel);
                }
                break;
            default:
                break;
        }
    }
    bool onClientConnection(std::shared_ptr<network::connection<protocol::Lobby>> client) override {
        return true;
    }

private:
    std::shared_ptr<network::data_channel<protocol::UDPProtocol>> _dataChannel = nullptr;
};


int main() {
    server srv(3030);
    srv.start();
    std::cout << "Server started" << std::endl;
    while (true) {
        srv.update(5, true);
    }
}