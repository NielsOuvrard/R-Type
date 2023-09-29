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
# ça compile pas sa mère sur macOS