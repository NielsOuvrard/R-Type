# TCP Protocol

The project make use of a TCP communication for creating the client-side communication.
As theses communications are not utilizing real-time data, but a request-response mechanism,
the use of the TCP protocol justified, as it enables a reliable traffic over network.

# Lobby Client networking

The client propose a set of lobby features that includes:

- lobby creation,
- lobby joining,
- lobby leaving,
- game starting,
- lobby chatroom.

Different views makes these features available to the user:

- lobby list view,
- lobby view.
- lobby administration

Once connected to the server the client will display all rooms availables to the user to select
and join. Once joined the interfaces changes to display a beautiful chat that makes it possible for
players to post and read messages.

# Lobby Protocol

The lobby protocol relies on a variety of requests and only 2 responses (ok, ko).

Current requests includes:

- room creation
- room joining
- room leaving
- room starting
- getting room list
- getting room details
- getting room chats

Current responses are:

- ok, returning a positive feedback on the result and containing information needed or requested.
- ko, referring to a faulty execution of the request and providing more insights about the incident.

Events:

- data channel, telling a client that a data channel will be opened and it needs to conenct
- new chat, telling a client in a lobby that a new chat as arrived

# Details

## Requests

| **create_room** | Type     | OK        |
|-----------------|----------|-----------|
| name            | char[32] | id uint32 |

| **join_room** | Type     | OK |
|---------------|----------|----|
| name          | char[32] |    |
| id            | uint32   |    |

| **leave_room** | Type   | OK |
|----------------|--------|----|
| id             | uint32 |    |

| **start_room** | Type   | OK |
|----------------|--------|----|
| id             | uint32 |    |

| **get_rooms** | Type | OK        |
|---------------|------|-----------|
|               |      | nb uint32 |
|               |      | [rooms]   |

| **get_room** | Type   | OK        |
|--------------|--------|-----------|
| id           | uint32 | nb uint32 |
|              |        | [members] |

| **get_chats** | Type   | OK        |
|---------------|--------|-----------|
| id            | uint32 | nb uint32 |
|               |        | [chats]   |

## Events

| **new_message** | Type      | 
|-----------------|-----------|
| sender          | char[32]  | 
| content         | char[128] | 

| **data_channel** | Type                    | 
|------------------|-------------------------|
| endpoint         | asio::ip::udp::endpoint |
