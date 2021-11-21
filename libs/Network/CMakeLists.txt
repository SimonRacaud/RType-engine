##
## PERSONAL PROJECT, 2021
## R-Type Project
## File description:
## R-Type CMake
##

cmake_minimum_required(VERSION 3.17)

set(CMAKE_BUILD_TYPE Release) # TEMPORARY

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(NAME Network)

project(R-Type VERSION 0.0.0 LANGUAGES CXX)

include_directories(
        ${CMAKE_INCLUDE_PATH}
        ./include/
        ../../common/include/Network/Tram
)

## SOURCES
set(SRCS
    src/Exceptions/NetworkException.cpp
    ../../common/src/Network/Tram/ComponentSync.cpp
    ../../common/src/Network/Tram/CreateEntityReply.cpp
    ../../common/src/Network/Tram/CreateEntityRequest.cpp
    ../../common/src/Network/Tram/DestroyEntity.cpp
    ../../common/src/Network/Tram/GetRoomList.cpp
    ../../common/src/Network/Tram/EndGame.cpp
    ../../common/src/Network/Serializable.cpp
    ../../common/src/Network/Tram/JoinCreateRoomReply.cpp
    ../../common/src/Network/Tram/JoinRoom.cpp
    ../../common/src/Network/Tram/TramBuffer.cpp
    ../../common/src/Network/NetworkManager.cpp
    src/DataWrapper.cpp
    )

## TARGET
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR})
add_library(${NAME} SHARED ${SRCS})

## COMPILATION FLAGS
if (MSVC)
    set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreadedDLL")
    target_compile_options(${NAME} PRIVATE)
else ()
    target_compile_options(${NAME} PRIVATE -Wall -Wextra -Wno-missing-field-initializers)
endif ()

## LIB
target_link_libraries(${NAME} ${CONAN_LIBS})

##
## CRITERION
## (c++17)
#set(NAME_TESTS unit_tests)
#add_executable(${NAME_TESTS}
#        ${SRCS}
#        tests/test_serializer.cpp
#        )
#target_link_libraries(${NAME_TESTS} criterion)