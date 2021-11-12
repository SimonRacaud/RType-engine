##
## PERSONAL PROJECT, 2021
## Babel Project
## File description:
## Babel CMake
##

cmake_minimum_required(VERSION 3.17)

set(CMAKE_BUILD_TYPE Debug) # TEMPORARY

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(NAME Network)

project(R-Type VERSION 0.0.0 LANGUAGES CXX)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

include_directories(
        ${CMAKE_INCLUDE_PATH}
        ./include/
)

## SOURCES
set(SRCS
        src/NetworkException.cpp
        src/Tram/ComponentSync.cpp
        src/Tram/CreateEntityReply.cpp
        )

## TARGET
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR})
add_library(${NAME} SHARED ${SRCS})

## COMPILATION FLAGS
if (MSVC)
    target_compile_options(${NAME} PRIVATE /W4 /WX)
else ()
    target_compile_options(${NAME} PRIVATE -Wall -Wextra -Wno-missing-field-initializers)
endif ()

## CONAN
target_link_libraries(${NAME} PUBLIC ${CONAN_LIBS})
