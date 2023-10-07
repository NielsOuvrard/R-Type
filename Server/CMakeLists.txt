cmake_minimum_required(VERSION 3.16)
project(r-type-server)

set(
    SOURCES
    src/main.cpp
    # ../Rtype/Rtype.cpp
)
    add_compile_options(-Wno-unused-command-line-argument)

add_executable(${PROJECT_NAME} ${SOURCES})
target_include_directories(${PROJECT_NAME} PUBLIC ../Rtype)
target_link_libraries(${PROJECT_NAME} PRIVATE haze)
target_link_libraries(${PROJECT_NAME} PRIVATE asio)
target_link_libraries(${PROJECT_NAME} PRIVATE rtype-game)

target_link_libraries(${PROJECT_NAME} PUBLIC Network)
target_include_directories(${PROJECT_NAME} PUBLIC .)