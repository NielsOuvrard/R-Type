cmake_minimum_required(VERSION 3.16)
project(rtype)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/)

add_subdirectory(Haze)
add_subdirectory(Server)
add_subdirectory(Client)
