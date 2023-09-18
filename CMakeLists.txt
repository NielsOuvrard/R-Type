cmake_minimum_required(VERSION 3.25)
project(rtype)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/)

add_subdirectory(Engine)
add_subdirectory(Server)
add_subdirectory(Client)
