##
## EPITECH PROJECT, 2021
## RType
## File description:
## PataPata cmake
##

cmake_minimum_required(VERSION 3.17)

set(CMAKE_BUILD_TYPE Release) # TODO : update after

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(NAME PataPata)

project(${NAME} VERSION 0.1 LANGUAGES CXX)

## INCLUDES
include_directories(
        ./
		../../../server/include/
)

## SOURCES
set(SRCS
		./PataPata.cpp)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC")

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/lib)
add_library(${NAME} SHARED ${SRCS})

if (WIN32)
    target_compile_options(${NAME} PRIVATE)
else ()
    target_compile_options(${NAME} PRIVATE -Wall -Wextra -fPIC)
endif ()