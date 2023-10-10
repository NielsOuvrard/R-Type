//
// Created by erwan on 9/29/23.
//

#include "common.h"
#include "net_client.h"
#include "net_data_channel.h"
#include "net_datagram.h"

using namespace std::chrono_literals;

class client : public network::client_interface<Protocol>
{
public:
    void start()
    {
        std::string entry;
        while (std::getline(std::cin, entry))
        {
            if (entry == "hello")
            {
                std::cout << "Hello!" << std::endl;
            }
            else if (entry == "connect")
            {
                if (!this->isConnected())
                    this->connect("127.0.0.1", 3030);
            }
            else if (entry == "update")
            {
                update();
            }
            else if (entry == "start")
            {
                std::cout << "Here\n";
                network::message<Protocol> msg = {Protocol::start_room, 0};
                this->send(msg);
            }
            else if (entry == "alive")
            {
                if (_dataChannel)
                {
                    network::datagram<UDPProtocol> data = {{UDPProtocol::alive, 0, std::chrono::system_clock::now()}};
                    _dataChannel->sendAll(data);
                }
            }
        }
    }

    void update()
    {
        if (this->isConnected())
        {
            while (!this->getIncoming().empty())
            {
                network::message<Protocol> msg = this->getIncoming().pop_front().content;
                switch (msg.header.id)
                {
                case Protocol::data_channel:
                    if (!_dataChannel)
                    {
                        asio::ip::udp::endpoint peer;
                        msg >> peer;
                        _dataChannel = std::make_unique<network::data_channel<UDPProtocol>>(this->_context);
                        _dataChannel->addPeer(peer);
                    }
                    break;
                default:
                    break;
                }
            }
        }
    }

private:
    std::unique_ptr<network::data_channel<UDPProtocol>> _dataChannel = nullptr;
};

int main()
{
    client cli;
    cli.start();
    return 0;
}
