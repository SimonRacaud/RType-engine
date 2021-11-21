##
## EPITECH PROJECT, 2021
## RType
## File description:
## PataPata cmake
##

cmake_minimum_required(VERSION 3.17)

set(CMAKE_BUILD_TYPE Release)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(NAME Cancer)

project(${NAME} VERSION 0.1 LANGUAGES CXX)

## INCLUDES
include_directories(
        ./
        ../../../server/include/
)

## SOURCES
set(SRCS
    ./Cancer.cpp)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/lib)
add_library(${NAME} SHARED ${SRCS})

if (WIN32)
    set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreadedDLL")
    target_compile_options(${NAME} PRIVATE)
else ()
    target_compile_options(${NAME} PRIVATE -Wall -Wextra -fPIC)
endif ()