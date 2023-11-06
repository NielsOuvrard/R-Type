cmake_minimum_required(VERSION 3.16)
project(rtype)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_compile_options(-Wno-unused-command-line-argument)

find_package(asio CONFIG REQUIRED)
find_package(SDL2 CONFIG REQUIRED)
find_package(SDL2_image CONFIG REQUIRED)
find_package(SDL2_mixer CONFIG REQUIRED)
find_package(SDL2_ttf CONFIG REQUIRED)


find_package(SFML COMPONENTS system window graphics audio CONFIG REQUIRED)

add_subdirectory(Protocols)
add_subdirectory(Network)
add_subdirectory(Haze)
add_subdirectory(Rtype)
add_subdirectory(Server)
add_subdirectory(Cocs-game)
add_subdirectory(Client)
