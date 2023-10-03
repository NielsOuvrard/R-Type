cmake_minimum_required(VERSION 3.25)
project(haze)
add_compile_options(-Wno-unused-command-line-argument)

option(WITH_GRAPHICS "Build with graphics" ON)
if (WITH_GRAPHICS)
    add_compile_definitions(USE_SFML)
endif()

set(
    SOURCES
    Entity/Entity.cpp
    System/System.cpp
    System/SystemGfx.cpp
    Engine/Engine.cpp
    ComponentList/ComponentList.cpp
    Pipeline/CorePipeline.cpp
    Pipeline/GfxPipeline.cpp

)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(haze STATIC ${SOURCES})
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/inc)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/System)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/Entity)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/Engine)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/Component)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/ComponentList)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/Pipeline)
target_link_libraries(${PROJECT_NAME} PUBLIC sfml-graphics sfml-window sfml-system)