cmake_minimum_required(VERSION 3.16)
project(r-type-client)
    add_compile_options(-Wno-unused-command-line-argument)

set(
    SOURCES
    src/main.cpp
    src/Rttype.cpp
    src/wall.cpp
)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(${PROJECT_NAME} ${SOURCES})
target_include_directories(${PROJECT_NAME} PRIVATE
    src
    includes
)

target_link_libraries(${PROJECT_NAME} PRIVATE
    haze-graphics
)
