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
set(OpenGL_GL_PREFERENCE GLVND)
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
    )

set(CMAKE_POSITION_INDEPENDENT_CODE ON)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR})
add_library(${NAME} ${SRCS})

## LIB

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}/cmake")
find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)
target_link_libraries(${NAME} sfml-graphics sfml-audio)