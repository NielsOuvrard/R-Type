cmake_minimum_required(VERSION 3.25)
project(r-type-server)

set(
    SOURCES
    src/main.cpp
)

add_executable(${PROJECT_NAME} ${SOURCES})
target_link_libraries(${PROJECT_NAME} PRIVATE haze)
