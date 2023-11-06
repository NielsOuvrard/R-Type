#pragma once

class Igame
{
public:
    virtual ~Igame() = default;
    virtual void start() = 0;
    virtual void stop() = 0;
    virtual void update() = 0;
    [[nodiscard]] virtual asio::ip::udp::endpoint getEndpoint() const = 0;
};