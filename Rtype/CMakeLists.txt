cmake_minimum_required(VERSION 3.25)
project(rtype-game)
add_compile_options(-Wno-unused-command-line-argument)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(
    SOURCES
    Rtype.cpp
    src/wall.cpp
)

add_library(${PROJECT_NAME} STATIC ${SOURCES})
target_compile_definitions(${PROJECT_NAME} PUBLIC USE_SFML=1)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} includes)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} src)
target_link_libraries(${PROJECT_NAME} PUBLIC
    haze-graphics
    Network
    protocols
)