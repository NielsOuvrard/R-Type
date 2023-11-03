//
// Created by erwan on 10/18/23.
//

#pragma once

#include "net_connection.h"
#include "protocols.h"
#include <iostream>
#include <memory>

class Room {
public:
    enum class privileges {
        owner,
        member,
    };

    struct chat_message {
        std::string sender;
        std::string content;
    };

public:
    explicit Room(uint32_t maxSize = 4);

public:
    [[nodiscard]] bool isOpen() const;
    [[nodiscard]] bool isFull();
    [[nodiscard]] std::size_t size();
    [[nodiscard]] bool canStart(const std::shared_ptr<network::connection<protocol::lobby>> &);
    [[nodiscard]] bool isMember(const std::shared_ptr<network::connection<protocol::lobby>> &);
    [[nodiscard]] const std::map<std::shared_ptr<network::connection<protocol::lobby>>, std::tuple<std::string, Room::privileges, bool>> &getMembers() const;
    bool disconnect(const std::shared_ptr<network::connection<protocol::lobby>> &);
    void addConnection(std::shared_ptr<network::connection<protocol::lobby>> &, char[32], privileges = privileges::member);
    const std::list<Room::chat_message> &getChats();
    void toggleReady(std::shared_ptr<network::connection<protocol::lobby>> &target);
    void close();

    void addChat(std::shared_ptr<network::connection<protocol::lobby>> &from, const std::string &content)
    {
        _chats.emplace_back(chat_message{std::get<0>(_members[from]), content});
    }


private:
    uint32_t maxSize;
    bool _open = true;
    std::list<chat_message> _chats;
    std::map<std::shared_ptr<network::connection<protocol::lobby>>, std::tuple<std::string, Room::privileges, bool>> _members;
};
