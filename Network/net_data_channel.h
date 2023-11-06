//
// Created by erwan on 10/3/23.
//

#pragma once

#include "net_common.h"
#include "net_datagram.h"
#include "net_message.h"
#include "net_tsqueue.h"

using namespace asio::ip;
using namespace std::chrono_literals;

namespace network {

    template<typename T>
    class data_channel {
    public:
        struct tracer {
            bool ack;
            uint32_t id;
            datagram<T> packet;
        };

        struct owned_tracer {
            udp::endpoint target;
            std::chrono::steady_clock::time_point tp;
            tracer data;
        };

    public:// Constructor destructor
        explicit data_channel(asio::io_context &context)
            : _context(context),
              _socket(context, udp::endpoint(udp::v4(), 0)),
              _timer(_context, asio::chrono::milliseconds(50))
        {
            asyncReceive();
            _timer.async_wait([this](const asio::error_code &ec) { asyncTracePkgs(ec, _timer); });
        };

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
                _outbox.push_back({to, std::chrono::steady_clock::now(), {false, _tracingCounter++, datagram}});
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

        void sendGroup(const datagram<T> &datagram)
        {
            for (auto &to: _group) {
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

        std::set<udp::endpoint> &getGroup() { return _group; };

    public:// Async Actions
        void asyncReceive()
        {
            _socket.async_receive_from(
                    asio::buffer(&_tracerBuffer, sizeof(tracer)),
                    _peerBuffer,
                    [this](std::error_code ec, std::size_t length) {
                        if (!ec) {
                            // std::cout << "[DATA] Received datagram" << std::endl;
                            auto [ack, id, data] = _tracerBuffer;
                            if (ack) {
                                std::scoped_lock lock(_tracingLock);
                                auto it = _tracingMap.find(id);// Find the iterator for the key
                                if (it != _tracingMap.end()) {
                                    _tracingMap.erase(it);// Erase the element using the iterator
                                    std::cout << "Packet #" << id << " acknowledged" << std::endl;
                                }
                            } else {
                                _inbox.push_back({_peerBuffer, data});
                                sendAck(_peerBuffer, id);
                            }
                            _peers.insert(_peerBuffer);
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
                            std::scoped_lock lock(_tracingLock);
                            auto trace = _outbox.pop_front();
                            trace.tp = std::chrono::steady_clock::now();
                            if (!trace.data.ack) {
                                _tracingMap[trace.data.id] = trace;
                            }
                            if (!_outbox.empty())
                                asyncWrite();
                        } else {
                            std::cerr << "[DATA] Failed to send datagram: " << ec.message() << std::endl;
                        }
                    });
        }

        void asyncTracePkgs(const asio::error_code &ec, asio::steady_timer &timer)
        {
            if (!ec) {
                std::cout << "Task executed" << std::endl;
                std::scoped_lock lock(_tracingLock);
                auto now = std::chrono::steady_clock::now();

                for (auto &pair: _tracingMap) {
                    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(now - pair.second.tp);
                    if (duration.count() > 200) {
                        std::cout << "ID: " << pair.first << " failed acknowledging" << std::endl;
                        bool writing = !_outbox.empty();
                        _outbox.push_back(pair.second);
                        if (!writing) {
                            asyncWrite();
                        }
                    }
                }

                // Reschedule the task
                timer.expires_at(timer.expiry() + asio::chrono::milliseconds(50));
                timer.async_wait([this](const asio::error_code &ec) { asyncTracePkgs(ec, _timer); });
            }
        }

    public:
        [[nodiscard]] udp::endpoint getEndpoint() const { return _socket.local_endpoint(); }

        void addPeer(const udp::endpoint &peer) { _peers.insert(peer); }

    private:
        void sendAck(const udp::endpoint &to, uint32_t id)
        {
            asio::post(_context, [this, to, id]() {
                bool writing = !_outbox.empty();
                _outbox.push_back({to, std::chrono::steady_clock::now(), {true, id}});
                if (!writing) {
                    asyncWrite();
                } });
        }

    private:// members
        asio::io_context &_context;
        udp::socket _socket;

        std::set<udp::endpoint> _peers;
        std::set<udp::endpoint> _group;

        ThreadSafeQueue<owned_datagram<T>> _inbox;
        ThreadSafeQueue<owned_tracer> _outbox;

        std::mutex _tracingLock;
        std::map<uint32_t, owned_tracer> _tracingMap;
        uint32_t _tracingCounter = 1;

        asio::steady_timer _timer;

        udp::endpoint _peerBuffer;
        tracer _tracerBuffer;
    };
}// namespace network
