##
## EPITECH PROJECT, 2021
## Indie Studio
## File description:
## Bomberman client
##

cmake_minimum_required(VERSION 3.17)

set(CMAKE_BUILD_TYPE Release)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(NAME eventTests)

project(${NAME} VERSION 0.1 LANGUAGES CXX)

## INCLUDES
include_directories(
        ../../../libs/GameEngine/include
        ../../../libs/GameEngine/include/Event
        ../../../libs/GameEngine/src/
        ../../../libs/GameEngine/src/Event/AbstractEvent
        ../../../libs/GameEngine/src/Event/EventCallBack/
        ../../../libs/GameEngine/src/Event/EventCallbackRegister    
        ./   
)

## SOURCES
set(SRCS
        main.cpp
        PrintingSystem.cpp
        )

add_executable(${NAME} ${SRCS})

if (MSVC)
    target_compile_options(${NAME} PRIVATE /W4 /WX)
else ()
    target_compile_options(${NAME} PRIVATE -Wall -Wextra)
endif ()

set(gameEngineDir /home/polo/Epitech/tek3/CPP-500/RType/libs/GameEngine)
add_subdirectory(${gameEngineDir} ${PROJECT_SOURCE_DIR}/lib)
target_link_libraries(${NAME} gameEngine)