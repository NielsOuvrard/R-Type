cmake_minimum_required(VERSION 3.16)
project(r-type-client)

set(
    SOURCES
    src/main.cpp
)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(SFML_ROOT "/opt/homebrew/Cellar/sfml/2.6.0")
set(SFML_INCLUDE_DIR "${SFML_ROOT}/include")
set(SFML_LIBRARY_DIR "${SFML_ROOT}/lib")

# Find the SFML components
find_package(SFML 2.5 COMPONENTS window graphics system REQUIRED)

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