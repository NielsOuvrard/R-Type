#pragma once

#include "net_common.h"
#include "net_message.h"
#include "net_tsqueue.h"

namespace network {
    template<typename T>
    class connection : public std::enable_shared_from_this<connection<T>> {
    public:
        enum class owner {
            client,
            server,
        };

    public:
        connection(owner parent, asio::io_context &context,
                   asio::ip::tcp::socket socket,
                   ThreadSafeQueue<owned_message<T>> &inbox)
            : _context(context), _socket(std::move(socket)), _inbox(inbox)
        {
            _owner = parent;
        }

        virtual ~connection() = default;

    public:
        void connectToServer(const asio::ip::tcp::endpoint endpoint)
        {
            if (_owner != owner::client)
                return;
            _socket.async_connect(endpoint, [this](std::error_code ec) {
                if (!ec) {
                    std::cout << "Client connected to remote endpoint." << std::endl;
                    asyncReadHeader();
                } else {
                    std::cerr << "Client connection error." << std::endl;
                }
            });
        }

        void startListening(uint32_t id)
        {
            if (_owner == owner::server && _socket.is_open()) {
                _id = id;
                asyncReadHeader();
            } else {
                std::cerr << "Failed to listen to socket" << std::endl
                          << "Socket: " << (_socket.is_open() ? "Open" : "Closed") << std::endl
                          << "Owner: " << (_owner == owner::server ? "Server" : "Client") << std::endl;
            }
        }

        bool isConnected() { return _socket.is_open(); }

        void disconnect()
        {
            if (isConnected()) {
                asio::post(_context, [this]() { _socket.close(); });
            }
        }

        bool operator==(const connection &rhs) const
        {
            return static_cast<const std::enable_shared_from_this<network::connection<T>> &>(*this) == static_cast<const std::enable_shared_from_this<network::connection<T>> &>(rhs) &&
                   _id == rhs._id;
        }

        bool operator!=(const connection &rhs) const
        {
            return !(rhs == *this);
        }

    public:
        void asyncReadHeader()
        {
            asio::async_read(
                    _socket,
                    asio::buffer(
                            &_messageBuffer.header, sizeof(message_header<T>)),
                    [this](std::error_code ec, std::size_t length) {
                        if (!ec) {
                            //                            std::cout << "[" << _id << "] Read " << length << "bytes" << std::endl;
                            if (_messageBuffer.header.size > 0) {
                                _messageBuffer.body.resize(_messageBuffer.header.size);
                                asyncReadBody();
                            } else {
                                addMessageToInbox();
                            }
                        } else {
                            // Reading went wrong
                            std::cerr << "[" << _id << "] Failed to read message header : "
                                      << ec.message()
                                      << std::endl
                                      << "Bytes read: "
                                      << length
                                      << std::endl;
                            // Likely a disconnect, see if it causes problems later
                            _socket.close();
                        }
                    });
        }

        void asyncReadBody()
        {
            asio::async_read(
                    _socket,
                    asio::buffer(_messageBuffer.body.data(), _messageBuffer.body.size()),
                    [this](std::error_code ec, std::size_t length) {
                        if (!ec) {
                            addMessageToInbox();
                        } else {
                            // Reading went wrong
                            std::cerr << "[" << _id << "] Failed to read message body"
                                      << std::endl;
                            // Likely a disconnect, see if it causes problems later
                            _socket.close();
                        }
                    });
        }

        void asyncWriteHeader()
        {
            //            std::cout << "writing\n";
            asio::async_write(
                    _socket, asio::buffer(&_outbox.front().header, sizeof(message_header<T>)),
                    [this](std::error_code ec, std::size_t length) {
                        if (!ec) {
                            //                            std::cout << length << "bytes were written successfully" << std::endl;
                            if (_outbox.front().body.size() > 0) {
                                asyncWriteBody();
                            } else {
                                _outbox.pop_front();
                                if (!_outbox.empty()) {
                                    asyncWriteHeader();
                                }
                            }
                        } else {
                            std::cout << "[" << _id << "] Write Header Fail.\n";
                            _socket.close();
                        }
                    });
        }

        void asyncWriteBody()
        {
            asio::async_write(_socket, asio::buffer(_outbox.front().body.data(), _outbox.front().body.size()),
                              [this](std::error_code ec, std::size_t length) {
                                  if (!ec) {
                                      _outbox.pop_front();
                                      if (!_outbox.empty()) {
                                          asyncWriteHeader();
                                      }
                                  } else {
                                      std::cout << "[" << _id << "] Write Body Fail.\n";
                                      _socket.close();
                                  }
                              });
        }

        void asyncSend(const message<T> &msg)
        {
            asio::post(_context, [this, msg]() {
                bool writing = !_outbox.empty();
                _outbox.push_back(msg);
                if (!writing) {
                    asyncWriteHeader();
                }
            });
        }

    public:
        void addMessageToInbox()
        {
            // Called when a message has been validated,
            // create a new owned message and add it to the inbox reference

            if (_owner == owner::server)
                _inbox.push_back({this->shared_from_this(), _messageBuffer});
            else
                _inbox.push_back({nullptr, _messageBuffer});

            // Ready to read the next message
            asyncReadHeader();
        }

        uint32_t getId() const { return _id; }

    protected:
        owner _owner = owner::server;
        asio::ip::tcp::socket _socket;
        asio::io_context &_context;

        ThreadSafeQueue<message<T>> _outbox;
        ThreadSafeQueue<owned_message<T>> &_inbox;

        message<T> _messageBuffer;

        uint32_t _id = 0;
    };
}// namespace network
