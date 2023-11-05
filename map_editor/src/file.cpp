#include "file.hpp"

void json_fill_EnemyData(EnemyData &data, nlohmann::json jsonData)
{
    data.damage = 0;
    data.life = 1;
    data.path_sprite = "";
    data.hitBoxData = {};
    data.shot_type = -1;
    data.fly = true;
    data.explosion_type = 0;
    data.type = jsonData["type"];
    data.height = 0;
    data.sound_spawn = "";
    data.sound_death = "";
    data.sound_damage = "";
    data.animation = {};

    if (jsonData.contains("damage")) {
        data.damage = jsonData["damage"];
    }
    if (jsonData.contains("life")) {
        data.life = jsonData["life"];
    }
    if (jsonData.contains("path_sprite")) {
        data.path_sprite = jsonData["path_sprite"];
    }
    if (jsonData.contains("hitbox")) {
        if (jsonData["hitbox"].contains("x"))
            data.hitBoxData.x = jsonData["hitbox"]["x"];
        if (jsonData["hitbox"].contains("y"))
            data.hitBoxData.y = jsonData["hitbox"]["y"];
        if (jsonData["hitbox"].contains("width"))
            data.hitBoxData.width = jsonData["hitbox"]["width"];
        if (jsonData["hitbox"].contains("height"))
            data.hitBoxData.height = jsonData["hitbox"]["height"];
    }
    if (jsonData.contains("shot_type")) {
        data.shot_type = jsonData["shot_type"];
    }
    if (jsonData.contains("fly")) {
        data.fly = jsonData["fly"];
    }
    if (jsonData.contains("explosion_type")) {
        data.explosion_type = jsonData["explosion_type"];
    }
    // if (jsonData.contains("animation") && jsonData["animation"].contains(0) && jsonData["animation"][0].contains("height")) {
    data.height = jsonData["animation"][0]["height"];
    // }
    if (jsonData.contains("sound_spawn")) {
        data.sound_spawn = jsonData["sound_spawn"];
    }
    if (jsonData.contains("sound_death")) {
        data.sound_death = jsonData["sound_death"];
    }
    if (jsonData.contains("sound_damage")) {
        data.sound_damage = jsonData["sound_damage"];
    }
    if (jsonData.contains("animation")) {// useless to put all the animation
        for (auto &animation: jsonData["animation"]) {
            HitBox tile_data;
            // * create enemy
            try {
                if (animation.contains("x") && animation.contains("y") && animation.contains("width") && animation.contains("height")) {
                    tile_data.x = animation["x"];
                    tile_data.y = animation["y"];
                    tile_data.width = animation["width"];
                    tile_data.height = animation["height"];
                    data.animation.push_back(tile_data);
                } else {
                    std::cerr << "Error parsing JSON\n";
                    exit(84);
                }
            } catch (nlohmann::json::parse_error &e) {
                std::cerr << "Error parsing JSON\n";
                std::cerr << e.what() << std::endl;
            }
        }
    }
}

void write_into_the_file(game_data &data)
{
    // create ne file
    std::ofstream fileStream(data.map_path);
    if (fileStream.is_open()) {
        fileStream << "{" << std::endl;
        fileStream << "  \"walls\": \"" << data.walls_paths[data.id_wall] << "\"," << std::endl;
        fileStream << "  \"parallax\": \"assets/sprites/space_night.jpg\"," << std::endl;// TODO
        fileStream << "  \"map\": [" << std::endl;
        int i = 0;
        for (auto &tile: data.tiles) {
            fileStream << "    {" << std::endl;
            fileStream << "      \"tile_top\": " << tile.tile_top << "," << std::endl;
            fileStream << "      \"tile_bottom\": " << tile.tile_bottom << (tile.enemies.size() > 0 ? "," : "") << std::endl;
            bool enemy_found = false;
            for (auto &enemy: data.enemies_on_map) {
                if (enemy.x < (i * SIZE_TILE) + SIZE_TILE && enemy.x >= (i * SIZE_TILE)) {
                    if (!enemy_found) {
                        fileStream << "      \"enemies\": [" << std::endl;
                        enemy_found = true;
                    }
                    fileStream << "        {" << std::endl;
                    fileStream << "          \"type\": " << enemy.type << "," << std::endl;
                    fileStream << "          \"x\": " << enemy.x << "," << std::endl;
                    fileStream << "          \"y\": " << enemy.y << "," << std::endl;
                    fileStream << "          \"velocity_x\": " << 0 << "," << std::endl;// TODO true values
                    fileStream << "          \"move\": \""
                               << "linear"
                               << "\"," << std::endl;
                    fileStream << "          \"move_time\": " << 0.05 << std::endl;
                    fileStream << "        }," << std::endl;
                }
            }
            if (enemy_found)
                fileStream << "      ]" << std::endl;
            if (&tile != &data.tiles.back())
                fileStream << "    }," << std::endl;
            else
                fileStream << "    }" << std::endl;
            i++;
        }
        fileStream << "  ]" << std::endl;
        fileStream << "}" << std::endl;
        fileStream.close();
    } else {
        std::cerr << "Failed to open file: " << data.map_path << std::endl;
        return;
    }
}

void event_handling(sf::RenderWindow &window, game_data &data)
{
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            window.close();
        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::A) {
            data.id_wall++;
            if (data.id_wall >= data.walls_paths.size())
                data.id_wall = 0;
        }
        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::S) {
            write_into_the_file(data);
        }
        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::L) {
            // add new tile
            tile new_tile = {};
            new_tile.tile_top = 0;
            new_tile.tile_bottom = 0;
            data.tiles.push_back(new_tile);
        }

        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::J) {
            // delete last tile
            if (data.tiles.size() > 1)
                data.tiles.pop_back();
        }
        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Left) {
            data.selected_tile--;
            if (data.selected_tile < 0)
                data.selected_tile = data.tiles.size() - 1;
            // if ((data.selected_tile + (data.x_shift * 2)) * SIZE_TILE * UNIVERSAL_SCALE < -(SIZE_TILE * UNIVERSAL_SCALE))
            //     data.x_shift = -((data.selected_tile - (WINDOW_WIDTH / (SIZE_TILE * UNIVERSAL_SCALE))) * 2);
        }
        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Right) {
            data.selected_tile++;
            if (data.selected_tile >= data.tiles.size())
                data.selected_tile = 0;
            // TODO
            // if (data.selected_tile * SIZE_TILE * UNIVERSAL_SCALE > WINDOW_WIDTH)
            //     data.x_shift = -((data.selected_tile - (WINDOW_WIDTH / (SIZE_TILE * UNIVERSAL_SCALE))) * 2);
        }
        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Up) {
            data.selected_tile_is_top = !data.selected_tile_is_top;
        }
        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Down) {
            data.selected_tile_is_top = !data.selected_tile_is_top;
        }

        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::I) {
            if (data.selected_tile_is_top) {
                data.tiles[data.selected_tile].tile_top++;
                if (data.tiles[data.selected_tile].tile_top >= data.nmb_tiles)
                    data.tiles[data.selected_tile].tile_top = 0;
            } else {
                data.tiles[data.selected_tile].tile_bottom++;
                if (data.tiles[data.selected_tile].tile_bottom >= data.nmb_tiles)
                    data.tiles[data.selected_tile].tile_bottom = 0;
            }
        }
        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::P) {
            data.id_enemy++;
            if (data.id_enemy >= data.nmb_enemies)
                data.id_enemy = 0;
            data.update_enemies = true;
        }
        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::O) {
            data.x_shift -= 1;
        }
        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::U) {
            data.x_shift += 1;
        }
        // mouse
        if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
            sf::Vector2i mousePos = sf::Mouse::getPosition(window);
            // add enemy
            EnemyData new_enemy = data.enemies[data.id_enemy];
            new_enemy.x = (mousePos.x / UNIVERSAL_SCALE) - (new_enemy.animation[0].width / 2) + (data.x_shift * (SIZE_TILE / 2));
            new_enemy.y = (mousePos.y / UNIVERSAL_SCALE) - (new_enemy.animation[0].height / 2);
            std::cout << "x: " << new_enemy.x << " y: " << new_enemy.y << std::endl;
            new_enemy.type = data.id_enemy;
            data.enemies_on_map.push_back(new_enemy);
        }
    }
}

void load_walls(game_data &data)
{
    const std::string directoryPath = "../assets/json_files/walls";

    for (const auto &entry: std::filesystem::directory_iterator(directoryPath)) {
        if (entry.is_regular_file() && entry.path().extension() == ".json") {
            std::string filePath = entry.path().string();
            data.walls_paths.push_back(filePath);
        }
    }
}

void load_enemies(game_data &data)
{
    const std::string directoryPath = "../assets/json_files/enemies";

    for (const auto &entry: std::filesystem::directory_iterator(directoryPath)) {
        if (entry.is_regular_file() && entry.path().extension() == ".json") {
            std::string filePath = entry.path().string();
            // data.enemies.push_back(filePath);
            std::ifstream fileStream(filePath);
            if (fileStream.is_open()) {
                try {
                    nlohmann::json jsonData;
                    fileStream >> jsonData;
                    EnemyData new_enemy_type;
                    json_fill_EnemyData(new_enemy_type, jsonData);
                    data.enemies.push_back(new_enemy_type);
                    sf::Texture texture_enemy = sf::Texture();
                    std::string path_enemy = "../" + new_enemy_type.path_sprite;
                    texture_enemy.loadFromFile(path_enemy);
                    data.textures.push_back(texture_enemy);
                    data.nmb_enemies++;
                } catch (nlohmann::json::parse_error &e) {
                    std::cerr << "Error parsing JSON file: " << filePath << std::endl;
                    std::cerr << e.what() << std::endl;
                    return;
                }
                fileStream.close();
            } else {
                std::cerr << "Failed to open file: " << filePath << std::endl;
                return;
            }
        }
    }
}

void fill_hitbox_wall(game_data &data, nlohmann::json jsonData)
{
    auto &walls_int_rect = jsonData;
    data.nmb_tiles = 0;
    if (walls_int_rect != nullptr) {
        for (auto &wall: walls_int_rect) {
            HitBox tile_data;
            // * create enemy
            try {
                if (wall.contains("x") && wall.contains("y") && wall.contains("width") && wall.contains("height")) {
                    tile_data.x = wall["x"];
                    tile_data.y = wall["y"];
                    tile_data.width = wall["width"];
                    tile_data.height = wall["height"];
                    data.wall_hitbox.push_back(tile_data);
                    data.nmb_tiles++;
                } else {
                    std::cerr << "Error parsing JSON\n";
                    exit(84);
                }
            } catch (nlohmann::json::parse_error &e) {
                std::cerr << "Error parsing JSON\n";
                std::cerr << e.what() << std::endl;
            }
        }
    } else {
        exit(84);
    }
}

int main(int ac, char **av)
{
    char *map_path = NULL;// put here parallax path and walls path
    if (av[1] != NULL)
        map_path = strdup(av[1]);
    else
        map_path = strdup("map.json");

    game_data data;
    data.map_path = map_path;
    data.id_wall = 0;
    data.x_shift = 0;
    data.selected_tile = 0;
    data.selected_tile_is_top = true;
    data.nmb_enemies = 0;
    data.id_enemy = 0;
    // data.universal_scale = UNIVERSAL_SCALE;
    load_walls(data);
    if (data.walls_paths.size() == 0) {
        std::cerr << "No walls found" << std::endl;
        return 84;
    }
    load_enemies(data);
    if (data.enemies.size() == 0) {
        std::cerr << "No enemies found" << std::endl;
        return 84;
    }

    std::string path_sprite_walls = "";
    std::ifstream fileStream(data.walls_paths[data.id_wall]);
    if (fileStream.is_open()) {
        try {
            nlohmann::json jsonData;
            fileStream >> jsonData;
            path_sprite_walls = jsonData["path_sprite"];
            fill_hitbox_wall(data, jsonData["animation"]);
        } catch (nlohmann::json::parse_error &e) {
            std::cerr << "Error parsing JSON file: " << data.walls_paths[data.id_wall] << std::endl;
            std::cerr << e.what() << std::endl;
            return 84;
        }
        fileStream.close();
    }

    // * create button
    ButtonElement button = ButtonElement(WINDOW_WIDTH - BUTTON_SIZE, 0, BUTTON_SIZE, BUTTON_SIZE, "Save");
    sf::Font font;
    font.loadFromFile("../assets/fonts/font.ttf");
    button.setFont(font);

    // * create wall
    sf::Sprite wall = sf::Sprite();
    sf::Texture texture_wall = sf::Texture();
    std::string path_wall = "../" + path_sprite_walls;
    texture_wall.loadFromFile(path_wall);
    wall.setTexture(texture_wall);
    wall.setScale(UNIVERSAL_SCALE, UNIVERSAL_SCALE);

    // * create enemy
    sf::Sprite enemy = sf::Sprite();
    enemy.setScale(UNIVERSAL_SCALE, UNIVERSAL_SCALE);

    tile new_tile = {};
    new_tile.tile_top = 0;
    new_tile.tile_bottom = 0;
    data.tiles.push_back(new_tile);

    sf::RectangleShape tile_selected_cursor = sf::RectangleShape(sf::Vector2f(SIZE_TILE * UNIVERSAL_SCALE, SIZE_TILE * UNIVERSAL_SCALE));
    sf::RectangleShape tool_side = sf::RectangleShape(sf::Vector2f(BUTTON_SIZE, WINDOW_HEIGHT));
    tool_side.setPosition(WINDOW_WIDTH - BUTTON_SIZE, 0);
    tool_side.setFillColor(sf::Color(0, 0, 0, 60));

    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Map Editor");
    window.setFramerateLimit(60);
    while (window.isOpen()) {
        data.update_enemies = false;
        window.clear(sf::Color::White);
        button.handleEvent(sf::Event(), window);
        event_handling(window, data);
        int i = 0;
        for (auto &tile: data.tiles) {
            // data.wall_hitbox[i]
            sf::IntRect rect = sf::IntRect(tile.tile_top * data.wall_hitbox[tile.tile_top].width, 0, data.wall_hitbox[tile.tile_top].width, data.wall_hitbox[tile.tile_top].height);
            wall.setTextureRect(rect);
            wall.setScale(UNIVERSAL_SCALE, UNIVERSAL_SCALE);
            wall.setPosition((i * SIZE_TILE + (data.x_shift * (SIZE_TILE / 2))) * UNIVERSAL_SCALE, 0);
            window.draw(wall);

            rect = sf::IntRect(tile.tile_bottom * data.wall_hitbox[tile.tile_bottom].width, 0, data.wall_hitbox[tile.tile_bottom].width, data.wall_hitbox[tile.tile_bottom].height);
            wall.setTextureRect(rect);
            wall.setScale(UNIVERSAL_SCALE, -UNIVERSAL_SCALE);
            wall.setPosition((i * SIZE_TILE + (data.x_shift * (SIZE_TILE / 2))) * UNIVERSAL_SCALE, WINDOW_HEIGHT);
            window.draw(wall);

            if (i == data.selected_tile) {
                if (data.selected_tile_is_top)
                    tile_selected_cursor = sf::RectangleShape(sf::Vector2f((data.wall_hitbox[tile.tile_top].width) * UNIVERSAL_SCALE, (data.wall_hitbox[tile.tile_top].height) * UNIVERSAL_SCALE));
                else
                    tile_selected_cursor = sf::RectangleShape(sf::Vector2f((data.wall_hitbox[tile.tile_bottom].width) * UNIVERSAL_SCALE, (data.wall_hitbox[tile.tile_bottom].height) * UNIVERSAL_SCALE));
                if (data.selected_tile_is_top)
                    tile_selected_cursor.setPosition((i * SIZE_TILE + (data.x_shift * (SIZE_TILE / 2))) * UNIVERSAL_SCALE, 0);
                else
                    tile_selected_cursor.setPosition((i * SIZE_TILE + (data.x_shift * (SIZE_TILE / 2))) * UNIVERSAL_SCALE, WINDOW_HEIGHT - (data.wall_hitbox[tile.tile_bottom].height) * UNIVERSAL_SCALE);
                tile_selected_cursor.setFillColor(sf::Color(255, 0, 0, 60));
                window.draw(tile_selected_cursor);
            }

            i++;
        }
        for (auto &enemy_on_map: data.enemies_on_map) {
            enemy.setTexture(data.textures[enemy_on_map.type]);
            sf::IntRect rect = sf::IntRect(data.enemies[enemy_on_map.type].animation[0].x, data.enemies[enemy_on_map.type].animation[0].y, data.enemies[enemy_on_map.type].animation[0].width, data.enemies[enemy_on_map.type].animation[0].height);
            enemy.setTextureRect(rect);
            // new_enemy.x = (mousePos.x / UNIVERSAL_SCALE) - (new_enemy.animation[0].width / 2) + (data.x_shift * (SIZE_TILE / 2));
            enemy.setPosition(((enemy_on_map.x + (data.x_shift * SIZE_TILE)) * UNIVERSAL_SCALE), enemy_on_map.y * UNIVERSAL_SCALE);
            window.draw(enemy);
        }
        button.render(window);

        window.draw(tool_side);

        enemy.setTexture(data.textures[data.id_enemy]);
        sf::IntRect rect = sf::IntRect(data.enemies[data.id_enemy].animation[0].x, data.enemies[data.id_enemy].animation[0].y, data.enemies[data.id_enemy].animation[0].width, data.enemies[data.id_enemy].animation[0].height);
        enemy.setTextureRect(rect);
        enemy.setPosition(WINDOW_WIDTH - (BUTTON_SIZE / 2) - (data.enemies[data.id_enemy].animation[0].width / 2), WINDOW_HEIGHT / 2);
        window.draw(enemy);

        window.display();
    }
    return 0;
}

// TODO cursor tile always on the screen, move shift if not
