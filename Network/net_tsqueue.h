#pragma once

#include "net_common.h"

namespace network {

    template<typename T>
    class ThreadSafeQueue {
    public:
        ThreadSafeQueue() = default;
        ThreadSafeQueue(const ThreadSafeQueue<T> &) = delete;
        virtual ~ThreadSafeQueue() { clear(); }

    public:
        void wait() {
            while (empty()) {
                std::unique_lock<std::mutex> ul(_mutexBlock);
                _cvBlock.wait(ul);
            }
        }

        const T& front()
        {
            std::scoped_lock lock(_mutexQueue);
            return _deQueue.front();
        }

        const T& back()
        {
            std::scoped_lock lock(_mutexQueue);
            return _deQueue.back();
        }

        T pop_front() {
            std::scoped_lock lock(_mutexQueue);
            auto t = std::move(_deQueue.front());
            _deQueue.pop_front();
            return t;
        }

        T pop_back() {
            std::scoped_lock lock(_mutexQueue);
            auto t = std::move(_deQueue.back());
            _deQueue.pop_back();
            return t;
        }

        void push_back(const T &item) {
            std::scoped_lock lock(_mutexQueue);
            _deQueue.emplace_back(std::move(item));

            std::unique_lock<std::mutex> ul(_mutexBlock);
            _cvBlock.notify_one();
        }

        void push_front(const T &item) {
            std::scoped_lock lock(_mutexQueue);
            _deQueue.emplace_front(std::move(item));

            std::unique_lock<std::mutex> ul(_mutexBlock);
            _cvBlock.notify_one();
        }

        bool empty() {
            std::scoped_lock lock(_mutexQueue);
            return _deQueue.empty();
        }

        std::size_t count() {
            std::scoped_lock lock(_mutexQueue);
            return _deQueue.size();
        }

        void clear() {
            std::scoped_lock lock(_mutexQueue);
            _deQueue.clear();
        }

    protected:
        std::mutex _mutexQueue;
        std::deque<T> _deQueue;

        std::mutex _mutexBlock;
        std::condition_variable _cvBlock;
    };

}// namespace network
