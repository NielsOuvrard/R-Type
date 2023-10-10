cmake_minimum_required(VERSION 3.25)
project(r-type-client)

add_compile_options(-Wno-unused-command-line-argument)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SOURCES
        client.cpp
        client.h
        main.cpp
        common.h
        components/TextInput.cpp
        components/TextInput.h
        components/Button.cpp
        components/Button.h
        components/Login.cpp
        components/Login.h
)

add_executable(${PROJECT_NAME} ${SOURCES})
target_include_directories(${PROJECT_NAME} PUBLIC inc)
target_link_libraries(${PROJECT_NAME} PRIVATE
        haze-graphics
        Network
)
