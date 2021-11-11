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


add_definitions("-fPIC")

project(R-Type
        VERSION 0.0.0
        LANGUAGES CXX)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()


include_directories(
        ${CMAKE_INCLUDE_PATH}
        include/
)

set(SRC_DIR src/)

############ CLIENT
set(CLIENT client)

## SOURCES
set(SRC_CLIENT ${SRC_DIR}/client/)


set(CLIENT_SRCS
    ${SRC_DIR}NetworkException.cpp

    ${SRC_CLIENT}/mainTestNetwork.cpp
    )

## TARGET
add_executable(${CLIENT} ${CLIENT_SRCS})

## INCLUDES
target_include_directories(${CLIENT} BEFORE PUBLIC include/client/)

## COMPILATION FLAGS
if (MSVC)
    target_compile_options(${CLIENT} PRIVATE /W4 /WX)
else ()
    target_compile_options(${CLIENT} PRIVATE -Wall -Wextra -Wno-missing-field-initializers)
endif ()

## DESTINATION
set_target_properties(${CLIENT} PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}")

## CONAN
target_link_libraries(${CLIENT} PUBLIC ${CONAN_LIBS})

############ SERVER
set(SERVER server)

## SOURCES
set(SRC_SERVER ${SRC_DIR}server/)

set(SERVER_SRCS
    ${SRC_DIR}NetworkException.cpp
    )

add_executable(${SERVER} ${SERVER_SRCS}
               ${SRC_SERVER}/mainTestNetwork.cpp
               )

## INCLUDES
target_include_directories(${SERVER} BEFORE PUBLIC include/server/)

## COMPILATION FLAGS
if (MSVC)
    target_compile_options(${SERVER} PRIVATE /W4 /WX)
else ()
    target_compile_options(${SERVER} PRIVATE -Wall -Wextra -Wno-missing-field-initializers)
endif ()

## DESTINATION
set_target_properties(${SERVER} PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}")

## LDD conan
target_link_libraries(${SERVER} PUBLIC ${CONAN_LIBS})