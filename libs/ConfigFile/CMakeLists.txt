##
## PERSONAL PROJECT, 2021
## singly Project
## File description:
## singly CMake
##

cmake_minimum_required(VERSION 3.17)

set(CMAKE_BUILD_TYPE Release)
#set(CMAKE_BUILD_TYPE Release)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(NAME ConfigFile)

project(${NAME} VERSION 0.0.1 LANGUAGES CXX)

## INCLUDES
include_directories(
        ./include
        ./src/
)

## SOURCES
set(SRCS
    src/ConfigFile.cpp
    src/ConfigFileTools/ConfigFileTools.cpp
    )

#set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR})
add_library(${NAME} SHARED ${SRCS})

if (WIN32)
    set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreadedDLL")
    target_compile_options(${NAME_CLIENT} PRIVATE)
else ()
    target_compile_options(${NAME_CLIENT} PRIVATE -g -Wall -Wextra -Wno-missing-field-initializers)
endif ()

## COMPILATION
target_compile_options(${NAME} PRIVATE)