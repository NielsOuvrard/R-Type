//
// Created by erwan on 9/29/23.
//

#include "common.h"
#include "net_data_channel.h"
#include "net_server.h"

class server : public network::server_interface<Protocol>
{
public:
    explicit server(uint16_t port) : network::server_interface<Protocol>(port) {}

protected:
    void onMessage(std::shared_ptr<network::connection<Protocol>> from, network::message<Protocol> &msg) override
    {
        switch (msg.header.id)
        {
        case Protocol::start_room:
            if (!_dataChannel)
            {
                _dataChannel = std::make_unique<network::data_channel<UDPProtocol>>(this->_context);
                network::message<Protocol> res = {{Protocol::data_channel, 0}};
                res << _dataChannel->getEndpoint();
                this->messageAllClient(res);
            }
            break;
        default:
            break;
        }
    }
    bool onClientConnection(std::shared_ptr<network::connection<Protocol>> client) override
    {
        return true;
    }

private:
    std::unique_ptr<network::data_channel<UDPProtocol>> _dataChannel = nullptr;
};
