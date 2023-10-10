cmake_minimum_required(VERSION 3.16)
project(r-type-client)

add_compile_options(-Wno-unused-command-line-argument)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SOURCES
        client.cpp
        client.h
        main.cpp
        common.h
        Elements/TextInput.cpp
        Elements/TextInput.h
        Elements/Button.cpp
        Elements/Button.h
        Elements/Login.cpp
        Elements/Login.h
        Elements/Element.h
)

add_executable(${PROJECT_NAME} ${SOURCES})
target_include_directories(${PROJECT_NAME} PUBLIC inc)
target_link_libraries(${PROJECT_NAME} PRIVATE
        haze-graphics
        Network
)
