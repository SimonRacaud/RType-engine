##
## EPITECH PROJECT, 2021
## r-type
## File description:
## r-type
##

cmake_minimum_required(VERSION 3.17)

set(CMAKE_BUILD_TYPE Release)

set(CMAKE_CXX_STANDARD 20)
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
    src/ColorLink/ColorLink.cpp
    src/TextManager/TextManager.cpp
    src/EventManager/EventManager.cpp
    src/ShapeManager/ShapeManager.cpp
    src/SpriteManager/SpriteManager.cpp
    src/WindowManager/WindowManager.cpp
    src/AnimationManager/AnimationManager.cpp
    src/AudioManager/MusicManager/MusicManager.cpp
    src/AudioManager/SoundManager/SoundManager.cpp
    src/SfmlApiManager/SfmlApiManager.cpp
    )

set(CMAKE_POSITION_INDEPENDENT_CODE ON)

#set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR})
add_library(${NAME} SHARED ${SRCS})

if (WIN32)
    set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreadedDLL")
    target_compile_options(${NAME_CLIENT} PRIVATE)
else ()
    target_compile_options(${NAME_CLIENT} PRIVATE -g -Wall -Wextra -Wno-missing-field-initializers)
endif ()

## LIB
target_link_libraries(${NAME} ${CONAN_LIBS})