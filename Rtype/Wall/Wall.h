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
#include "../config.h"
#include "GameStructures.h"
#include <Factory.hpp>
#include <haze-core.hpp>
#include <haze-graphics.hpp>
#include <net_data_channel.h>
#include <protocol.h>
#include <utility>

/**
 * @class Wall
 *
 * @brief Represents a wall object in the game.
 *
 * The `Wall` class is responsible for managing wall objects in the game. Walls can be constructed,
 * updated, and destroyed. They are used for level design and as game obstacles.
 */
class Wall {
public:
    /**
     * @brief Constructs a Wall object.
     *
     * @param engine The game engine.
     * @param channel The data channel for network communication.
     * @param dataJSON JSON data representing the wall's properties.
     * @param x The X-coordinate of the wall's position.
     * @param y The Y-coordinate of the wall's position.
     * @param isGround Specifies whether the wall is a ground object.
     */
    Wall(DataGame _dataGame, nlohmann::json dataJSON, float x, float y, bool isGround, std::string wall_json_path);

    /**
     * @brief Builds the wall object.
     *
     * This function constructs the wall object based on its properties.
     *
     * @param frameIndex The index of the frame to use for the wall (optional).
     */
    void build(uint16_t frameIndex = 0);

    /**
     * @brief Sends the wall data to clients.
     *
     * This function sends the wall data to clients using the network channel.
     */
    void send();

    /**
     * @brief Stop the movement of walls, and send it to client.
     *
     * Useful for the end of the map
     */
    void stopVelocity();

    /**
     * @brief Destroys the wall object.
     *
     * This function destroys the wall object, removing it from the game.
     */
    void destroy();

    /**
     * @brief Retrieves the X-coordinate of the wall's position.
     *
     * @return The X-coordinate of the wall's position.
     */
    [[nodiscard]] float get_x_position() const;

private:
    DataGame _dataGame;

    std::vector<Haze::Animation::intRect> _frames;
    uint8_t _frameIndex = 0;
    float _x;
    float _y;
    uint32_t _id;
    bool _isGround;
    std::string _wall_json_path;

    Haze::Entity *_entity = nullptr;
    nlohmann::json _dataJSON;
};
