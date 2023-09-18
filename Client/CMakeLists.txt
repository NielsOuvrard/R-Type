cmake_minimum_required(VERSION 3.25)
project(r-type-client)

set(
    SOURCES
    src/main.cpp
)

add_executable(${PROJECT_NAME} ${SOURCES})
