cmake_minimum_required(VERSION 3.25)
project(r-type-client)

add_compile_options(-Wno-unused-command-line-argument)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SOURCES
        client.cpp
        client.h
        main.cpp
        Elements/TextInput.cpp
        Elements/TextInput.h
        Elements/Button.cpp
        Elements/Button.h
        Elements/Element.h
        spectator.cpp
        spectator.h
        Cooldown.h
        Cooldown.cpp
        Scenes/Login.cpp
        Scenes/Login.h
        Elements/Image.cpp
        Elements/Image.h
        Scenes/Background.cpp
        Scenes/Background.h
)

add_executable(${PROJECT_NAME} ${SOURCES})
target_link_libraries(${PROJECT_NAME} PRIVATE
        haze-graphics
        Network
        protocols
)
