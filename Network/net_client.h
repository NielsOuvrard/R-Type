#pragma once

#include "net_common.h"
#include "net_connection.h"
#include "net_tsqueue.h"

namespace network {
    template<typename T>
    class client_interface {
    public:
        client_interface() = default;

        virtual ~client_interface()
        {
            disconnect();
        }

    public:
        bool connect(const std::string &ip, uint16_t port)
        {
            try {
                // creating the endpoint and connection
                asio::ip::tcp::endpoint endpoint(asio::ip::make_address(ip), port);
                _connection = std::make_unique<connection<T>>(connection<T>::owner::client, _context,
                                                              asio::ip::tcp::socket(_context), _inbox);

                _connection->connectToServer(endpoint);
                if (!_contextThread.joinable()) {
                    _contextThread = std::thread([this]() { _context.run(); });
                }
            } catch (std::exception &e) {
                std::cerr << "Client Exception: " << e.what() << std::endl;
                return false;
            }
            return true;
        }

        bool isConnected()
        {
            if (_connection)
                return _connection->isConnected();
            return false;
        };

        void disconnect()
        {
            if (isConnected()) {
                _connection->disconnect();
            }
            _context.stop();
            if (_contextThread.joinable()) {
                _contextThread.join();
            }
            _connection.release();
        }

    public:
        void send(const message<T> &msg)
        {
            if (isConnected())
                _connection->asyncSend(msg);
            else
                std::cerr << "Not Connected\n";
        }

        ThreadSafeQueue<owned_message<T>> &getIncoming() { return _inbox; }

    protected:
        asio::io_context _context;
        std::thread _contextThread;
        std::unique_ptr<connection<T>> _connection;

    private:
        ThreadSafeQueue<owned_message<T>> _inbox;
    };
}// namespace network
