//
// Created by erwan on 9/29/23.
//

// #include "common.h"
#include "Rtype.hpp"
#include "data.h"
#include "lobby.h"
#include "net_connection.h"
#include "net_data_channel.h"
#include "net_server.h"

class server : public network::server_interface<protocol::lobby>
{
public:
    explicit server(uint16_t port) : network::server_interface<protocol::lobby>(port) {}

protected:
    void onMessage(std::shared_ptr<network::connection<protocol::lobby>> from, network::message<protocol::lobby> &msg) override
    {
        switch (msg.header.id)
        {
        case protocol::lobby::start_room:
            if (!_dataChannel)
            {
                _dataChannel = std::make_shared<network::data_channel<protocol::data>>(this->_context);
                // network::message<protocol::lobby> res = {{protocol::lobby::data_channel, 0}};
                network::message<protocol::lobby> res;
                res.header.id = protocol::lobby::data_channel;
                res.header.size = 0;

                res << _dataChannel->getEndpoint();
                this->messageAllClient(res);
                Rtype rtype(this->_context);
                rtype.run(_dataChannel);
            }
            break;
        default:
            break;
        }
    }

    bool onClientConnection(std::shared_ptr<network::connection<protocol::lobby>> client) override
    {
        return true;
    }

private:
    std::shared_ptr<network::data_channel<protocol::data>> _dataChannel = nullptr;
};

int main()
{
    server srv(3030);
    srv.start();
    std::cout << "Server started" << std::endl;
    while (true)
    {
        srv.update(5, true);
    }
}
