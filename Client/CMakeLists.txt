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
        Scenes/LobbyList.cpp
        Scenes/LobbyList.h
        Elements/Text.cpp
        Elements/Text.h
        Scenes/LobbyList.cpp
        Scenes/LobbyItem.cpp
        Scenes/LobbyItem.h
        Scenes/Lobby.cpp
        Scenes/Lobby.h
        Elements/Chat.cpp
        Elements/Chat.h
        Elements/UserCard.cpp
        Elements/UserCard.h
)

add_executable(${PROJECT_NAME} ${SOURCES})
target_link_libraries(${PROJECT_NAME} PRIVATE
        haze-graphics
        Network
        protocols
)
