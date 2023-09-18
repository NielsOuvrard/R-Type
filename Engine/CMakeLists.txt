cmake_minimum_required(VERSION 3.25)
project(haze)

set(
    SOURCES
    src/hello.cpp
)

add_library(haze STATIC ${SOURCES})
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/inc)
