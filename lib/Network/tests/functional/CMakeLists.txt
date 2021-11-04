##
## PERSONAL PROJECT, 2021
## Babel Project
## File description:
## Babel CMake
##

cmake_minimum_required(VERSION 3.17)

set(CMAKE_BUILD_TYPE Debug)

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
        include
)

set(SRC_DIR src/)

############## TEST
####### Client
set(CLIENT client)
set(CLIENT_DIR ${SRC_DIR}${CLIENT}/)

## SOURCES
set(SRCS_CLIENT
    ${CLIENT_DIR}testClientTCP.cpp
    )

## TARGET
add_executable(${CLIENT}
               ${SRCS_CLIENT}
               ${CLIENT_DIR}/mainTestClientNetwork.cpp
               )


## INCLUDES
target_include_directories(${CLIENT} BEFORE PUBLIC include)
target_include_directories(${CLIENT} BEFORE PUBLIC ${CMAKE_HOME_DIRECTORY}/../../include/)

## COMPILATION FLAGS
if (MSVC)
    target_compile_options(${CLIENT} PRIVATE /W4 /WX)
else ()
    target_compile_options(${CLIENT} PRIVATE -Wall -Wextra -Wno-missing-field-initializers)
endif ()

## DESTINATION
set_target_properties(${CLIENT} PROPERTIES RUNTIME_OUTPUT_DIRECTORY "..")

## LDD conan
target_link_libraries(${CLIENT} PUBLIC ${CONAN_LIBS})


####### Server
set(SERVER server)
set(SERVER_DIR ${SRC_DIR}${SERVER}/)

## SOURCES
set(SRCS_SERVER
    ${SERVER_DIR}testServerTCP.cpp
    )

add_executable(${SERVER}
               ${SRCS_SERVER}
#               ${SERVER_DIR}/mainSTestServerNetwork.cpp
               /home/arthur/Epitek/Epi_workinonit/R-Type/lib/Network/tests/functional/src/server/mainTestServerNetwork.cpp
               )

## INCLUDES
target_include_directories(${SERVER} BEFORE PUBLIC include)
target_include_directories(${SERVER} BEFORE PUBLIC ${CMAKE_HOME_DIRECTORY}/../../include/)

## COMPILATION FLAGS
if (MSVC)
    target_compile_options(${SERVER} PRIVATE /W4 /WX)
else ()
    target_compile_options(${SERVER} PRIVATE -Wall -Wextra -Wno-missing-field-initializers)
endif ()

## DESTINATION
set_target_properties(${SERVER} PROPERTIES RUNTIME_OUTPUT_DIRECTORY "..")

## LDD conan
target_link_libraries(${SERVER} PUBLIC ${CONAN_LIBS})