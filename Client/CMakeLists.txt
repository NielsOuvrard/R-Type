cmake_minimum_required(VERSION 3.16)
project(r-type-client)

set(
    SOURCES
    src/main.cpp
)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(${PROJECT_NAME} ${SOURCES})

# Link your executable with the SFML libraries
target_link_libraries(${PROJECT_NAME}
    sfml-window
    sfml-graphics
    sfml-system
    sfml-audio
    haze
)

# Include the SFML headers
target_include_directories(${PROJECT_NAME} PRIVATE ${SFML_INCLUDE_DIR})