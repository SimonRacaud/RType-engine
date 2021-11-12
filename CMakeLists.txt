##
## EPITECH PROJECT, 2021
## R-Type
## File description:
## C++ Program
##

cmake_minimum_required(VERSION 3.17)

#set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_BUILD_TYPE Release)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(NAME_CLIENT r-type_client)
set(NAME_SERVER r-type_server)

project(${NAME_CLIENT} VERSION 0.1 LANGUAGES CXX)
project(${NAME_SERVER} VERSION 0.1 LANGUAGES CXX)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

## GLOBAL INCLUDES
include_directories(./include)
include_directories(./server/src/DLLoader)

##
## CLIENT
##
## SOURCES
set(CLIENT_SRCS
        client/src/main.cpp
        client/src/ConfigFileExternal/ConfigFileExternal.cpp
        client/src/Scene/Start/StartScene.cpp
        client/src/System/RenderSystem/RenderSystem.cpp
        client/src/System/LogPosition/LogPositionSystem.cpp
        client/src/System/InputEventSystem/InputEventSystem.cpp
        client/src/Event/AudioEvent/AudioEventManager/AudioEventManager.cpp
        client/src/Scene/Debug/DebugScene.cpp
        client/src/Events/TimerEvent.hpp
        client/src/GameCore/GameCore.cpp
        client/src/Entities/Button/Button.cpp
        client/src/Component/Scroll.hpp
        client/src/System/ScrollSystem/ScrollSystem.cpp
        client/src/Scene/Home/HomeScene.cpp client/src/Scene/Home/HomeScene.hpp client/src/Scene/Settings/SettingsScene.cpp client/src/Scene/Settings/SettingsScene.hpp client/src/Scene/Game/GameScene.cpp client/src/Scene/Game/GameScene.hpp client/src/Scene/RoomList/RoomListScene.cpp client/src/Scene/RoomList/RoomListScene.hpp
        server/src/DLLoader/DLLoader.hpp
        client/src/Entities/ImageView/ImageView.cpp
        client/src/Entities/Label/Label.cpp)

add_executable(${NAME_CLIENT} ${CLIENT_SRCS})

target_include_directories(${NAME_CLIENT} PUBLIC client/src client/include)

if (WIN32)
    target_compile_options(${NAME_CLIENT} PRIVATE)
else ()
    target_compile_options(${NAME_CLIENT} PRIVATE -g -Wall -Wextra -Wno-missing-field-initializers)
endif ()

set_target_properties(${NAME_CLIENT}
        PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}"
        )
##
## SERVER
##
## SOURCES
set(SERVER_SRCS
        ./server/src/main.cpp
        ./server/src/GameStage/GameStage.cpp
        ./server/src/DLLoader/DLLoader.hpp
        )

add_executable(${NAME_SERVER} ${SERVER_SRCS})

target_include_directories(${NAME_SERVER} PUBLIC sever/src server/include)

if(MSVC)
    set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS TRUE)
    set(BUILD_SHARED_LIBS TRUE)
endif()

if (WIN32)
    target_compile_options(${NAME_SERVER} PRIVATE)
else ()
    target_compile_options(${NAME_SERVER} PRIVATE -Wall -Wextra -Wno-missing-field-initializers)
endif ()

set_target_properties(${NAME_SERVER}
        PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}"
        )

## GAME-ENGINE (client & server)
set(GAME_ENGINE_DIR ${PROJECT_SOURCE_DIR}/libs/GameEngine)
add_subdirectory(${PROJECT_SOURCE_DIR}/libs/GameEngine/)
include_directories(${GAME_ENGINE_DIR}/include ${GAME_ENGINE_DIR}/src)
target_link_libraries(${NAME_CLIENT} gameEngine)

## CONFIG_FILE (client & server)
set(ConfigFileDir ${PROJECT_SOURCE_DIR}/libs/ConfigFile)
add_subdirectory(${ConfigFileDir})
include_directories(${ConfigFileDir}/include)
include_directories(${ConfigFileDir}/src/ConfigFileTools)
target_link_libraries(${NAME_CLIENT} ConfigFile)
target_link_libraries(${NAME_SERVER} ConfigFile)

## SFML (client)
set(SfmlDir ${PROJECT_SOURCE_DIR}/libs/Sfml)
add_subdirectory(${SfmlDir})
include_directories(${SfmlDir}/include)
include_directories(${SfmlDir}/src)
target_link_libraries(${NAME_CLIENT} Sfml)