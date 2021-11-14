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
    src/Exceptions/NetworkException.cpp
    src/Tram/ComponentSync.cpp
    src/Tram/CreateEntityReply.cpp
    src/Tram/CreateEntityRequest.cpp
    src/Tram/DestroyEntity.cpp
    src/Tram/GetRoomList.cpp
    src/Tram/Serializable.cpp
    src/Tram/JoinCreateRoomReply.cpp
    src/Tram/JoinRoom.cpp
    src/Tram/TramBuffer.cpp
    src/NetworkManager.cpp
    src/DataWrapper.cpp
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

##
## CRITERION
## (c++17)

set(NAME_TESTS unit_tests)
add_executable(${NAME_TESTS}
               ${SRCS}
               tests/test_serializer.cpp
               )
target_link_libraries(${NAME_TESTS} criterion)

## CONAN
target_link_libraries(${NAME} PUBLIC ${CONAN_LIBS})