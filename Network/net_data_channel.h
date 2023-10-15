//
// Created by erwan on 10/3/23.
//

#pragma once

#include "net_common.h"
#include "net_datagram.h"
#include "net_message.h"
#include "net_tsqueue.h"

using namespace asio::ip;

namespace network {
    template<typename T>
    class data_channel {
    public:// Constructor destructor
        explicit data_channel(asio::io_context &context)
            : _context(context),
              _socket(context, udp::endpoint(udp::v4(), 0)) { asyncReceive(); };

        virtual ~data_channel() = default;


    public:// Receiving information
        void startListening()
        {
            try {
                asyncReceive();
            } catch (std::exception &e) {
                std::cerr << "]";
            }
        }

    public:// Sending information
        void sendTo(const datagram<T> &datagram, const udp::endpoint &to)
        {
            asio::post(_context, [this, datagram, to]() {
                bool writing = !_outbox.empty();
                _outbox.push_back({to, datagram});
                if (!writing) {
                    asyncWrite();
                } });
        }

        void sendAll(const datagram<T> &datagram)
        {

            for (auto &to: _peers) {
                sendTo(datagram, to);
            }
        }

        void sendSome(const datagram<T> &datagram, std::vector<udp::endpoint> some)
        {

            for (auto &to: some) {
                sendTo(datagram, to);
            }
        }

    public:
        void update(size_t maxDatagram = -1, bool wait = false)
        {

            if (wait) _inbox.wait();
            size_t count = 0;
            while (count < maxDatagram && !_inbox.empty()) {
                owned_datagram<T> msg = _inbox.pop_front();
                onReceive(msg.target, msg.data);
                count++;
            }
        }

        virtual void onReceive(udp::endpoint from, datagram<T> content){};

        ThreadSafeQueue<owned_datagram<T>> &getIncoming() { return _inbox; }


    public:// Async Actions
        void asyncReceive()
        {
            _socket.async_receive_from(
                    asio::buffer(&_datagramBuffer, sizeof(datagram<T>)),
                    _peerBuffer,
                    [this](std::error_code ec, std::size_t length) {
                        if (!ec) {
                            // std::cout << "[DATA] Received datagram" << std::endl;
                            _peers.insert(_peerBuffer);
                            _inbox.push_back({_peerBuffer, _datagramBuffer});
                            asyncReceive();
                        } else {
                            std::cerr << "[DATA] failed to read data: " << ec.message() << std::endl;
                        }
                    });
        }

        void asyncWrite()
        {
            _socket.async_send_to(
                    asio::buffer(&_outbox.front().data, 1024),
                    _outbox.front().target,
                    [this](std::error_code ec, std::size_t length) {
                        if (!ec) {
                            //std::cout << "[DATA] datagram sent" << std::endl;
                            _outbox.pop_front();
                            if (!_outbox.empty())
                                asyncWrite();
                        } else {
                            std::cerr << "[DATA] Failed to send datagram: " << ec.message() << std::endl;
                        }
                    });
        }

    public:
        [[nodiscard]] udp::endpoint getEndpoint() const { return _socket.local_endpoint(); }

        void addPeer(const udp::endpoint &peer) { _peers.insert(peer); }

    private:// members
        asio::io_context &_context;
        udp::socket _socket;

        std::set<udp::endpoint> _peers;

        ThreadSafeQueue<owned_datagram<T>> _inbox;
        ThreadSafeQueue<owned_datagram<T>> _outbox;

        udp::endpoint _peerBuffer;
        datagram<T> _datagramBuffer;
    };
}// namespace network
