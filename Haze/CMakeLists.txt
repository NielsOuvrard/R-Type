cmake_minimum_required(VERSION 3.25)
project(haze)
add_compile_options(-Wno-unused-command-line-argument)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../Haze/lib/)
set(CMAKE_SHARED_LIBRARY_PREFIX "")

set(
        SOURCES_CORE
        Entity/Entity.cpp
        System/core/SystemCore.cpp
        Engine/Engine.cpp
        Factory/Factory.cpp
        ComponentList/ComponentList.cpp
        Pipeline/core/CorePipeline.cpp
)
add_library(haze STATIC ${SOURCES_CORE})
target_include_directories(haze PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/inc)
target_include_directories(haze PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/System/core)
target_include_directories(haze PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/Entity)
target_include_directories(haze PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/Engine)
target_include_directories(haze PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/Component)
target_include_directories(haze PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/ComponentList)
target_include_directories(haze PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/Pipeline)
target_include_directories(haze PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/Factory)
target_include_directories(haze PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/Pipeline/core)


set(
        SOURCES_GRAPHICS
        Entity/Entity.cpp
        System/core/SystemCore.cpp
        System/gfx/SystemGfx.cpp
        Engine/Engine.cpp
        Factory/Factory.cpp
        ComponentList/ComponentList.cpp
        Pipeline/core/CorePipeline.cpp
        Pipeline/gfx/GfxPipeline.cpp
        DynLib/DynLib.cpp
        Component/ComponentGfx.cpp
)

set(
        SFML_SOURCES
        IDisplay/SfDisplay.cpp
)

add_library(rtype_sfml SHARED ${SFML_SOURCES})
target_include_directories(rtype_sfml PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(rtype_sfml PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/IDisplay)
target_include_directories(rtype_sfml PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/inc)
target_include_directories(rtype_sfml PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/AssetManager)

add_library(haze-graphics STATIC ${SOURCES_GRAPHICS})
target_link_libraries(rtype_sfml PUBLIC sfml-graphics sfml-window sfml-system sfml-audio)
target_compile_definitions(haze-graphics PUBLIC USE_SFML=1)
target_include_directories(haze-graphics PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/inc)
target_include_directories(haze-graphics PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/System/gfx)
target_include_directories(haze-graphics PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/System/core)
target_include_directories(haze-graphics PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/Entity)
target_include_directories(haze-graphics PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/Engine)
target_include_directories(haze-graphics PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/Component)
target_include_directories(haze-graphics PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/ComponentList)
target_include_directories(haze-graphics PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/Pipeline)
target_include_directories(haze-graphics PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/Pipeline/gfx)
target_include_directories(haze-graphics PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/Factory)
target_include_directories(haze-graphics PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/Pipeline/core)
target_include_directories(haze-graphics PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/IDisplay)
target_include_directories(haze-graphics PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/AssetManager)
target_include_directories(haze-graphics PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/DynLib)
target_link_libraries(haze-graphics PUBLIC sfml-graphics sfml-window sfml-system sfml-audio)