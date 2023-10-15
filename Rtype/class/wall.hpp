/*
** ooooooooo.           ooooooooooooo
** `888   `Y88.         8'   888   `8
**  888   .d88'              888      oooo    ooo oo.ooooo.   .ooooo.
**  888ooo88P'               888       `88.  .8'   888' `88b d88' `88b
**  888`88b.    8888888      888        `88..8'    888   888 888ooo888
**  888  `88b.               888         `888'     888   888 888    .o
** o888o  o888o             o888o         .8'      888bod8P' `Y8bod8P'
**                                    .o..P'       888
**                                    `Y8P'       o888o
**
** Wall
*/

#pragma onces

#include "../../Haze/inc/json.hpp"
#include <haze-core.hpp>
#include <haze-graphics.hpp>
#include <net_data_channel.h>
#include <protocol.h>
#include <Factory.hpp>

class wall {
public:
    wall::wall(Haze::Engine &engine, network::data_channel<protocol::data> &channel, nlohmann::json dataJSON, float x, float y);
    void build();
    void update();
    void send();
    void sendUpdate();

private:
    Haze::Engine &_engine;
    network::data_channel<protocol::data> &_channel;

    std::vector<Haze::Animation::intRect> _frames;
    float _x;
    float _y;

    Haze::Entity *_entity;
    nlohmann::json _dataJSON;
};
