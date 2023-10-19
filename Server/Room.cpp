//
// Created by erwan on 10/18/23.
//

#include "Room.h"

Room::Room(uint32_t maxSize) : maxSize(maxSize) {}

void Room::addConnection(std::shared_ptr<network::connection<protocol::lobby>> &con, char *name, Room::privileges permissions)
{
    _members[con] = std::make_tuple(name, permissions);
}

std::size_t Room::size()
{
    return _members.size();
}

bool Room::isOpen() const
{
    return _open;
}

bool Room::isFull()
{
    return size() >= maxSize;
}

bool Room::disconnect(const std::shared_ptr<network::connection<protocol::lobby>> &target)
{
    return _members.erase(target) == 1;
}

bool Room::canStart(const std::shared_ptr<network::connection<protocol::lobby>> &target)
{
    return std::get<1>(_members[target]) == privileges::owner;
}

bool Room::isMember(const std::shared_ptr<network::connection<protocol::lobby>> &target)
{
    return _members.find(target) != _members.end();
}

const std::map<std::shared_ptr<network::connection<protocol::lobby>>, std::tuple<std::string, Room::privileges>> &Room::getMembers() const
{
    return _members;
}

const std::list<Room::chat_message> &Room::getChats()
{
    return _chats;
}
