##
## EPITECH PROJECT, 2021
## r-type
## File description:
## r-type
##

cmake_minimum_required(VERSION 3.17)

set(CMAKE_BUILD_TYPE Release)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(NAME Sfml)

project(${NAME} VERSION 0.1 LANGUAGES CXX)

## INCLUDES
include_directories(
        ./include
        ./src
)

## SOURCES
set(SRCS
    src/SfmlModule.cpp
    src/EventManager/EventManager.cpp
    src/WindowManager/WindowManager.cpp
    src/AudioManager/MusicManager/MusicManager.cpp
    src/AudioManager/SoundManager/SoundManager.cpp
    )

set(CMAKE_POSITION_INDEPENDENT_CODE ON)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR})
add_library(${NAME} ${SRCS})

## LIB
target_link_libraries(${NAME} ${CONAN_LIBS})