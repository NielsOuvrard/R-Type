#pragma once

#include "net_common.h"
#include "net_connection.h"
#include "net_message.h"
#include "net_tsqueue.h"

namespace network {

    template<typename T>
    class server_interface {
    public:
        explicit server_interface(uint16_t port)
            : _acceptor(_context,
                        asio::ip::tcp::endpoint(asio::ip::tcp::v4(), port)){};

        virtual ~server_interface() { stop(); }

    public:
        void start()
        {
            try {
                asyncWaitForClientsConnection();
                _contextThread = std::thread([this]() { _context.run(); });
            } catch (std::exception &e) {
                std::cerr << "Server failed to start: " << e.what() << std::endl;
            }
        }

        void stop()
        {
            _context.stop();
            if (_contextThread.joinable())
                _contextThread.join();
            std::cout << "Server stopped" << std::endl;
        }

        bool isRunning() { return false; }

    public:
        void messageClient(std::shared_ptr<connection<T>> client, const message<T> &msg)
        {
            if (client && client->isConnected()) {
                client->asyncSend(msg);
            } else {
                onClientDisconnect(client);
                client.reset();
                _clients.erase(std::remove(_clients.begin(), _clients.end(), client), _clients.end());
            }
        }

        void messageAllClient(const message<T> &msg)
        {
            bool invalidClientExists = false;

            for (std::shared_ptr<connection<T>> &client: _clients) {
                if (client && client->isConnected()) {
                    client->asyncSend(msg);
                } else {
                    onClientDisconnect(client);
                    client.reset();
                    invalidClientExists = true;
                }
            }
            // cleanup after iteration
            if (invalidClientExists)
                _clients.erase(std::remove(_clients.begin(), _clients.end(), nullptr), _clients.end());
        }

    public:
        void asyncWaitForClientsConnection()
        {
            _acceptor.async_accept([this](std::error_code ec,
                                          asio::ip::tcp::socket socket) {
                if (!ec) {
                    std::cout << "[SERVER] Accepted incoming connection" << std::endl;

                    // create the client connection
                    std::shared_ptr<connection<T>> con = std::make_shared<connection<T>>(
                            connection<T>::owner::server, _context, std::move(socket), _inbox);

                    if (onClientConnection(con)) {
                        _clients.push_back(std::move(con));
                        _clients.back()->startListening(_idCounter++);
                    } else {
                    }

                } else {
                    std::cerr << "[SERVER] Refused incoming connection" << std::endl;
                }
                asyncWaitForClientsConnection();
            });
        }

    public:
        void update(size_t maxMessage = -1, bool wait = false)
        {
            if (wait) _inbox.wait();

            size_t msgCount = 0;
            while (msgCount < maxMessage && !_inbox.empty()) {
                auto msg = _inbox.pop_front();
                onMessage(msg.owner, msg.content);
                msgCount++;
            }
        }

    protected:
        virtual bool onClientConnection(std::shared_ptr<connection<T>> client) { return false; }

        virtual void onClientDisconnect(std::shared_ptr<connection<T>> client) {}

        virtual void onMessage(std::shared_ptr<connection<T>> from, message<T> &msg) {}

    protected:
        asio::io_context _context;
        std::thread _contextThread;

        // tcp acceptor for handling incoming connection
        asio::ip::tcp::acceptor _acceptor;

        ThreadSafeQueue<owned_message<T>> _inbox;
        std::deque<std::shared_ptr<connection<T>>> _clients;

        uint32_t _idCounter = 1;
    };

}// namespace network
