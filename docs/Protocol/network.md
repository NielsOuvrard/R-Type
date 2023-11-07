# How does it works

The networking utilises the Asio library for asynchronous networking out of the box.

We developed a small framework on top of it, capable of handling
any type of data through templates, and allowing to use it as a distinct library.

# Manipulate data!

Using the given options you can manipulate incoming and outgoing data on the network.
You can utilise the virtual to override event methods `onConnect`, `onDisconnect`
, `onMessage`, `onSend`...

Or you can directy manage the update cycle of the outbox and the inbox.

# Packet loss handling

For handling packet losses, the framework encapsulate the datagram inside a tracer.
The tracer goal is to time and track the acknowledgement state of a sent packet.

When the packet is marqued as lost by a slave async task running on the asio context,
a new paquet containing the same old data is sent to the original target.
