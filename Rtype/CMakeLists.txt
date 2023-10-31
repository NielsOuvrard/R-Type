cmake_minimum_required(VERSION 3.25)
project(rtype-game)
add_compile_options(-Wno-unused-command-line-argument)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(
        SOURCES
        Rtype.cpp
        Wall/Wall.cpp
        protocol.h
        Player/Player.cpp
        Player/Player.h
        Cooldown/Cooldown.cpp
        Cooldown/Cooldown.h
        Missile/Missile.cpp
        Missile/Missile.h
        Enemy/Enemy.cpp
        Enemy/Enemy.h
        Enemy/EnemyData.h
        Paralax/Paralax.cpp
        Paralax/Paralax.h
        Explosion/Explosion.cpp
        Explosion/Explosion.h
        MapHandling/MapHandling.cpp
        MapHandling/MapHandling.h
        config.h
        Boss/Boss.cpp
        Boss/Boss.h
        Boss/BossData.h
        processJsonFilesInDirectory.cpp
)

add_library(${PROJECT_NAME} STATIC ${SOURCES})
target_compile_definitions(${PROJECT_NAME} PUBLIC USE_SFML=1)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} inc)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} class)
target_link_libraries(${PROJECT_NAME} PUBLIC
        haze-graphics
        Network
        protocols
)
