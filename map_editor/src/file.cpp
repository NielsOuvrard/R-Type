#include "file.hpp"

void json_fill_EnemyData(EnemyData &data, nlohmann::json jsonData)
{
    data.id = 0;
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
        fileStream << "  \"walls\": \""
                   << data.paths_walls[data.id_wall]
                   << "\"," << std::endl;// TODO data.walls_paths[data.id_wall]
        fileStream << "  \"parallax\": \"" << data.parallax_path << "\"," << std::endl;
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
                    fileStream << "          \"x\": " << std::round(enemy.x) << "," << std::endl;
                    fileStream << "          \"y\": " << std::round(enemy.y) << "," << std::endl;
                    fileStream << "          \"velocity_x\": " << data.types_velocity_enemy[data.id_type_velocity_enemy] << "," << std::endl;
                    fileStream << "          \"move\": \"" << data.types_move_enemy[data.id_type_move_enemy] << "\"," << std::endl;
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

void event_handling(sf::RenderWindow &window, game_data &data, sf::View &view)
{
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            window.close();
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
                data.selected_tile = 0;
            // if view is not on the screen, move it
            if (data.selected_tile * SIZE_TILE * UNIVERSAL_SCALE < view.getCenter().x - (WINDOW_WIDTH / 2))
                view.move(-((SIZE_TILE / 2) * UNIVERSAL_SCALE), 0.0f);
        }
        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Right) {
            data.selected_tile++;
            if (data.selected_tile >= data.tiles.size())
                data.selected_tile = data.tiles.size() - 1;
            // if view is not on the screen, move it
            if (data.selected_tile * SIZE_TILE * UNIVERSAL_SCALE > view.getCenter().x + (WINDOW_WIDTH / 2))
                view.move(((SIZE_TILE / 2) * UNIVERSAL_SCALE), 0.0f);
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
        }
        // mouse
        if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
            sf::Vector2i mousePos = sf::Mouse::getPosition(window);
            // click in tool side
            if (mousePos.x > WINDOW_WIDTH - BUTTON_SIZE) {
                if (mousePos.y > WINDOW_HEIGHT - BUTTON_SIZE) {
                    // change velocity enemy
                    data.id_type_velocity_enemy++;
                    if (data.id_type_velocity_enemy >= data.types_velocity_enemy.size())
                        data.id_type_velocity_enemy = 0;
                    data.button_velocity_enemy.setSubTextString(std::to_string(data.types_velocity_enemy[data.id_type_velocity_enemy]));
                } else if (mousePos.y > WINDOW_HEIGHT - (BUTTON_SIZE * 2)) {
                    // change move enemy
                    data.id_type_move_enemy++;
                    if (data.id_type_move_enemy >= data.types_move_enemy.size())
                        data.id_type_move_enemy = 0;
                    data.button_move_enemy.setSubTextString(data.types_move_enemy[data.id_type_move_enemy]);
                } else if (mousePos.y > WINDOW_HEIGHT - (BUTTON_SIZE * 3)) {
                    // change wall
                    data.id_wall++;
                    if (data.id_wall >= data.nmb_walls)
                        data.id_wall = 0;
                } else if (mousePos.y > WINDOW_HEIGHT - (BUTTON_SIZE * 4)) {
                    // delete enemy
                    if (data.enemies_on_map.size() > 0)
                        data.enemies_on_map.pop_back();
                } else if (mousePos.y > WINDOW_HEIGHT - (BUTTON_SIZE * 5)) {
                    // change enemy
                    data.id_enemy++;
                    if (data.id_enemy >= data.nmb_enemies)
                        data.id_enemy = 0;
                } else if (mousePos.y > WINDOW_HEIGHT - (BUTTON_SIZE * 6)) {
                    // save
                    std::cout << "Saved" << std::endl;
                    write_into_the_file(data);
                }
                return;
            }
            // add enemy
            EnemyData new_enemy = data.enemies[data.id_enemy];
            new_enemy.x = ((mousePos.x + view.getCenter().x - (WINDOW_WIDTH / 2)) / UNIVERSAL_SCALE) - (new_enemy.animation[0].width / 2);
            new_enemy.y = (mousePos.y / UNIVERSAL_SCALE) - (new_enemy.animation[0].height / 2);
            new_enemy.id = data.id_enemy;
            data.enemies_on_map.push_back(new_enemy);
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

void load_walls(game_data &data)
{
    const std::string directoryPath = "../assets/json_files/walls";
    data.nmb_walls = 0;
    data.id_wall = 0;
    for (const auto &entry: std::filesystem::directory_iterator(directoryPath)) {
        if (entry.is_regular_file() && entry.path().extension() == ".json") {
            std::string filePath = entry.path().string();
            std::ifstream fileStream(filePath);
            if (fileStream.is_open()) {
                try {
                    nlohmann::json jsonData;
                    fileStream >> jsonData;
                    std::string path_sprite_walls = jsonData["path_sprite"];
                    fill_hitbox_wall(data, jsonData["animation"]);

                    sf::Texture texture_wall = sf::Texture();
                    std::string path_wall = "../" + path_sprite_walls;
                    texture_wall.loadFromFile(path_wall);

                    data.textures_walls.push_back(texture_wall);
                    data.paths_walls.push_back(path_sprite_walls);
                    data.nmb_walls++;

                } catch (nlohmann::json::parse_error &e) {
                    std::cerr << "Error parsing JSON file: " << filePath << std::endl;
                    std::cerr << e.what() << std::endl;
                    return;
                }
                fileStream.close();
            }
        }
    }

    if (data.textures_walls.size() == 0)
        exit(84);
}

void load_enemies(game_data &data)
{
    const std::string directoryPath = "../assets/json_files/enemies";

    for (const auto &entry: std::filesystem::directory_iterator(directoryPath)) {
        if (entry.is_regular_file() && entry.path().extension() == ".json") {
            std::string filePath = entry.path().string();
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
                    data.textures_enemy.push_back(texture_enemy);
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

int main(int argc, char **argv)
{
    std::string map_path = "map.json";
    std::string parallax_path = "assets/sprites/space.jpg";

    for (int i = 1; i < argc; i++) {
        std::string arg = argv[i];
        if (arg == "-name" && i + 1 < argc) {
            map_path = argv[i + 1];
            i++;
        } else if (arg == "-parallax" && i + 1 < argc) {
            parallax_path = argv[i + 1];
            i++;
        } else {
            std::cerr << "Unknown or incomplete option: " << arg << std::endl;
            return 1;
        }
    }

    // parallax
    game_data data;
    data.map_path = map_path;
    data.parallax_path = parallax_path;

    data.selected_tile = 0;
    data.selected_tile_is_top = true;
    data.id_enemy = 0;
    data.nmb_enemies = 0;
    data.id_type_move_enemy = 0;
    data.types_move_enemy = {"linear", "sinusoidal", "circular"};
    data.id_type_velocity_enemy = 0;
    data.types_velocity_enemy = {0, 2, 5, -2};

    load_walls(data);
    if (data.textures_walls.size() == 0) {
        std::cerr << "No walls found" << std::endl;
        return 84;
    }
    load_enemies(data);
    if (data.enemies.size() == 0) {
        std::cerr << "No enemies found" << std::endl;
        return 84;
    }

    // * create parallax
    sf::Sprite parallax = sf::Sprite();
    parallax.setScale(2, 2);
    sf::Texture texture_parallax = sf::Texture();
    std::string parallax_path_load = "../" + parallax_path;
    texture_parallax.loadFromFile(parallax_path_load);
    parallax.setTexture(texture_parallax);

    // * create wall
    sf::Sprite wall = sf::Sprite();
    wall.setScale(UNIVERSAL_SCALE, UNIVERSAL_SCALE);

    // * create view_map
    sf::View view_map(sf::FloatRect(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT));
    view_map.setViewport(sf::FloatRect(0, 0, 1.0f, 1.0f));

    // * create view_tool
    sf::View view_tool(sf::FloatRect(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT));
    view_tool.setViewport(sf::FloatRect(0, 0, 1.0f, 1.0f));

    // * create buttons
    sf::Font font;
    font.loadFromFile("../assets/fonts/font.ttf");

    data.button_save = ButtonElement(WINDOW_WIDTH - BUTTON_SIZE, 0, BUTTON_SIZE, BUTTON_SIZE, "Save");
    data.button_save.setFont(font);
    data.button_enemy = ButtonElement(WINDOW_WIDTH - BUTTON_SIZE, BUTTON_SIZE, BUTTON_SIZE, BUTTON_SIZE, "Enemy");
    data.button_enemy.setFont(font);
    data.button_delete_enemy = ButtonElement(WINDOW_WIDTH - BUTTON_SIZE, BUTTON_SIZE * 2, BUTTON_SIZE, BUTTON_SIZE, "Delete");
    data.button_delete_enemy.setFont(font);
    data.button_delete_enemy.setSubTextString("Enemy");
    data.button_wall = ButtonElement(WINDOW_WIDTH - BUTTON_SIZE, BUTTON_SIZE * 3, BUTTON_SIZE, BUTTON_SIZE, "Wall");
    data.button_wall.setFont(font);
    data.button_move_enemy = ButtonElement(WINDOW_WIDTH - BUTTON_SIZE, BUTTON_SIZE * 4, BUTTON_SIZE, BUTTON_SIZE, "Move:");
    data.button_move_enemy.setFont(font);
    data.button_move_enemy.setSubTextString(data.types_move_enemy[data.id_type_move_enemy]);
    data.button_velocity_enemy = ButtonElement(WINDOW_WIDTH - BUTTON_SIZE, BUTTON_SIZE * 5, BUTTON_SIZE, BUTTON_SIZE, "Velocity:");
    data.button_velocity_enemy.setFont(font);
    data.button_velocity_enemy.setSubTextString(std::to_string(data.types_velocity_enemy[data.id_type_velocity_enemy]));

    // * create enemy
    sf::Sprite enemy = sf::Sprite();
    enemy.setScale(UNIVERSAL_SCALE, UNIVERSAL_SCALE);

    tile new_tile = {};
    new_tile.tile_top = 0;
    new_tile.tile_bottom = 0;
    data.tiles.push_back(new_tile);

    sf::RectangleShape tile_selected_cursor = sf::RectangleShape(sf::Vector2f(SIZE_TILE * UNIVERSAL_SCALE, SIZE_TILE * UNIVERSAL_SCALE));


    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Map Editor");
    window.setFramerateLimit(60);
    while (window.isOpen()) {
        enemy.setOrigin(0, 0);
        window.clear(sf::Color::White);
        wall.setTexture(data.textures_walls[data.id_wall]);
        event_handling(window, data, view_map);
        data.button_save.handleEvent(sf::Event(), window);
        data.button_enemy.handleEvent(sf::Event(), window);
        data.button_delete_enemy.handleEvent(sf::Event(), window);
        data.button_wall.handleEvent(sf::Event(), window);
        data.button_move_enemy.handleEvent(sf::Event(), window);
        data.button_velocity_enemy.handleEvent(sf::Event(), window);

        int i = 0;
        window.draw(parallax);
        window.setView(view_map);
        for (auto &tile: data.tiles) {
            // data.wall_hitbox[i]
            sf::IntRect rect = sf::IntRect(tile.tile_top * data.wall_hitbox[tile.tile_top].width, 0, data.wall_hitbox[tile.tile_top].width, data.wall_hitbox[tile.tile_top].height);
            wall.setTextureRect(rect);
            wall.setScale(UNIVERSAL_SCALE, UNIVERSAL_SCALE);
            wall.setPosition((i * SIZE_TILE) * UNIVERSAL_SCALE, 0);
            window.draw(wall);

            rect = sf::IntRect(tile.tile_bottom * data.wall_hitbox[tile.tile_bottom].width, 0, data.wall_hitbox[tile.tile_bottom].width, data.wall_hitbox[tile.tile_bottom].height);
            wall.setTextureRect(rect);
            wall.setScale(UNIVERSAL_SCALE, -UNIVERSAL_SCALE);
            wall.setPosition((i * SIZE_TILE) * UNIVERSAL_SCALE, WINDOW_HEIGHT);
            window.draw(wall);

            if (i == data.selected_tile) {
                if (data.selected_tile_is_top)
                    tile_selected_cursor = sf::RectangleShape(sf::Vector2f((data.wall_hitbox[tile.tile_top].width) * UNIVERSAL_SCALE, (data.wall_hitbox[tile.tile_top].height) * UNIVERSAL_SCALE));
                else
                    tile_selected_cursor = sf::RectangleShape(sf::Vector2f((data.wall_hitbox[tile.tile_bottom].width) * UNIVERSAL_SCALE, (data.wall_hitbox[tile.tile_bottom].height) * UNIVERSAL_SCALE));
                if (data.selected_tile_is_top)
                    tile_selected_cursor.setPosition((i * SIZE_TILE) * UNIVERSAL_SCALE, 0);
                else
                    tile_selected_cursor.setPosition((i * SIZE_TILE) * UNIVERSAL_SCALE, WINDOW_HEIGHT - (data.wall_hitbox[tile.tile_bottom].height) * UNIVERSAL_SCALE);
                tile_selected_cursor.setFillColor(sf::Color(255, 0, 0, 60));
                window.draw(tile_selected_cursor);
            }
            i++;
        }
        for (auto &enemy_on_map: data.enemies_on_map) {
            enemy.setTexture(data.textures_enemy[enemy_on_map.id]);
            sf::IntRect rect = sf::IntRect(data.enemies[enemy_on_map.id].animation[0].x, data.enemies[enemy_on_map.id].animation[0].y, data.enemies[enemy_on_map.id].animation[0].width, data.enemies[enemy_on_map.id].animation[0].height);
            enemy.setTextureRect(rect);
            enemy.setPosition(enemy_on_map.x * UNIVERSAL_SCALE, enemy_on_map.y * UNIVERSAL_SCALE);
            window.draw(enemy);
        }
        window.setView(view_tool);
        data.button_save.render(window);
        data.button_enemy.render(window);
        data.button_delete_enemy.render(window);
        data.button_wall.render(window);
        data.button_move_enemy.render(window);
        data.button_velocity_enemy.render(window);

        enemy.setTexture(data.textures_enemy[data.id_enemy]);
        sf::IntRect rect = sf::IntRect(data.enemies[data.id_enemy].animation[0].x, data.enemies[data.id_enemy].animation[0].y, data.enemies[data.id_enemy].animation[0].width, data.enemies[data.id_enemy].animation[0].height);
        enemy.setTextureRect(rect);
        enemy.setOrigin(data.enemies[data.id_enemy].animation[0].width / 2, data.enemies[data.id_enemy].animation[0].height / 2);
        enemy.setPosition(WINDOW_WIDTH - (BUTTON_SIZE / 2), 160);

        window.draw(enemy);

        window.display();
    }
    return 0;
}
