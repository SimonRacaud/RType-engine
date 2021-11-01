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
set(NAME gameEngine)

project(${NAME} VERSION 0.1 LANGUAGES CXX)

## INCLUDES
include_directories(
        ./include
        ./src/
        ./src/BaseComponent
        ./src/ComponentManager
        ./src/EntityManager
)

## SOURCES
set(SRCS
        # Exception
        src/Exception/BasicException.cpp
        src/ComponentManager/ComponentManager.cpp
        src/ComponentTypeRegister/ComponentTypeRegister.hpp
        src/EntityManager/EntityManager.cpp
        src/EntityRegister/EntityRegister.cpp
        src/EntityRegister/EntityBlock.cpp
        src/NetworkIdRegister/NetworkIdRegister.cpp)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR})
add_library(${NAME} ${SRCS})

if (MSVC)
    target_compile_options(${NAME} PRIVATE /W4 /WX)
else ()
    target_compile_options(${NAME} PRIVATE -Wall -Wextra)
endif ()