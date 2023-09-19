cmake_minimum_required(VERSION 3.16)
project(r-type-client)

set(
    SOURCES
    src/main.cpp
)

add_executable(${PROJECT_NAME} ${SOURCES})
