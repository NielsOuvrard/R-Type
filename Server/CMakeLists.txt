cmake_minimum_required(VERSION 3.16)
project(r-type-server)

add_compile_options(-Wno-unused-command-line-argument)

set(SOURCES
        main.cpp
        server.cpp
        Room.cpp
        Room.h
)

add_executable(${PROJECT_NAME} ${SOURCES})
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(${PROJECT_NAME} PRIVATE
        haze-core
        Network
        rtype-game
        Cocs-game
)
