cmake_minimum_required(VERSION 3.26)
project(r-type-server)

set(
    SOURCES
    src/main.cpp
    # ../Rtype/Rtype.cpp
)
    add_compile_options(-Wno-unused-command-line-argument)

add_executable(${PROJECT_NAME} ${SOURCES})
target_include_directories(${PROJECT_NAME} PUBLIC ../Rtype)
target_link_libraries(${PROJECT_NAME} PRIVATE
    haze
    Network
    rtype-game
)
