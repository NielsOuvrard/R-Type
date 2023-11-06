cmake_minimum_required(VERSION 3.16)
project(rtype)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_compile_options(-Wno-unused-command-line-argument)

# Fetching Asio
# Asio is header only, so we don't need to build it
# We can just use it as an interface library
include(FetchContent)
FetchContent_Declare(
        asio
        GIT_REPOSITORY https://github.com/chriskohlhoff/asio.git
        GIT_TAG asio-1-28-0
)

# Check if asio is already populated
# If not, then we populate it
FetchContent_GetProperties(asio)
if (NOT asio_POPULATED)
    FetchContent_Populate(asio)
endif ()

# Add asio as an interface library
find_package(Threads REQUIRED)
add_library(asio INTERFACE)
target_include_directories(asio INTERFACE ${asio_SOURCE_DIR}/asio/include)
target_link_libraries(asio INTERFACE Threads::Threads)

# Fetching SFML
FetchContent_Declare(
        sfml
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG 2.6.0
)
FetchContent_MakeAvailable(sfml)

# Fetching sdl2
FetchContent_Declare(
        sdl2
        GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
        GIT_TAG release-2.28.4
        GIT_PROGRESS    TRUE
)
FetchContent_MakeAvailable(sdl2)

FetchContent_Declare(
        sdl2_image
        GIT_REPOSITORY https://github.com/libsdl-org/SDL_image.git
        GIT_TAG release-2.6.3
        GIT_PROGRESS    TRUE
)
FetchContent_MakeAvailable(sdl2_image)

FetchContent_Declare(
        sdl2_ttf
        GIT_REPOSITORY https://github.com/libsdl-org/SDL_ttf.git
        GIT_TAG release-2.20.2
        GIT_PROGRESS    TRUE
)
FetchContent_MakeAvailable(sdl2_ttf)

if(NOT CMAKE_SYSTEM_NAME STREQUAL "Darwin")
        FetchContent_Declare(
                sdl2_mixer
                GIT_REPOSITORY https://github.com/libsdl-org/SDL_mixer.git
                GIT_TAG release-2.6.3
                GIT_PROGRESS    TRUE
        )
        FetchContent_MakeAvailable(sdl2_mixer)
endif()


add_subdirectory(Protocols)
add_subdirectory(Network)
add_subdirectory(Haze)
add_subdirectory(Rtype)
add_subdirectory(Server)
add_subdirectory(Client) # comment
