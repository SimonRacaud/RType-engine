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
set(COMMON_PROJECT_SRC
    ../../src/Exceptions/NetworkException.cpp
    ../../src/Tram/CreateEntityReply.cpp
    ../../src/Tram/ComponentSync.cpp
    ../../src/Tram/TramBuffer.cpp)

############## EXECUTABLES
####### Server
set(SERVER server)
set(SERVER_DIR ${SRC_DIR}${SERVER}/)

## SOURCES
set(SRCS_SERVER
    ${SERVER_DIR}testServerTCP.cpp
    ${SERVER_DIR}testServerTCPdataWrapper.cpp
    )

add_executable(${SERVER}
               ${SRCS_SERVER}
               ${COMMON_PROJECT_SRC}
               ${SERVER_DIR}/mainTestServerNetwork.cpp
               )

## INCLUDES
target_include_directories(${SERVER} BEFORE PUBLIC include)
target_include_directories(${SERVER} BEFORE PUBLIC ${CMAKE_HOME_DIRECTORY}/../../include/)
target_include_directories(${SERVER} BEFORE PUBLIC ${CMAKE_HOME_DIRECTORY}/../../include/utils)

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


####### Client
set(CLIENT client)
set(CLIENT_DIR ${SRC_DIR}${CLIENT}/)

## SOURCES
set(SRCS_CLIENT
    ${CLIENT_DIR}testClientTCP.cpp
    ${CLIENT_DIR}testClientTCPdataWrapper.cpp
    )

## TARGET
add_executable(${CLIENT}
               ${SRCS_CLIENT}
               ${COMMON_PROJECT_SRC}
               ${CLIENT_DIR}/mainTestClientNetwork.cpp
               )


## INCLUDES
target_include_directories(${CLIENT} BEFORE PUBLIC include)
target_include_directories(${CLIENT} BEFORE PUBLIC ${CMAKE_HOME_DIRECTORY}/../../include/)
target_include_directories(${CLIENT} BEFORE PUBLIC ${CMAKE_HOME_DIRECTORY}/../../include/utils)

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

####### Independent
set(INDEPENDENT independent)
set(INDEPENDENT_DIR ${SRC_DIR}${INDEPENDENT}/)

## SOURCES
set(SRCS_INDEPENDENT
    ${INDEPENDENT_DIR}testTramBuffer.cpp
    )

## TARGET
add_executable(${INDEPENDENT}
               ${COMMON_PROJECT_SRC}
               ${SRCS_INDEPENDENT}
               ${INDEPENDENT_DIR}/mainTestIndependent.cpp
               )


## INCLUDES
target_include_directories(${INDEPENDENT} BEFORE PUBLIC include)
target_include_directories(${INDEPENDENT} BEFORE PUBLIC ${CMAKE_HOME_DIRECTORY}/../../include/)
target_include_directories(${INDEPENDENT} BEFORE PUBLIC ${CMAKE_HOME_DIRECTORY}/../../include/utils)

## COMPILATION FLAGS
if (MSVC)
    target_compile_options(${INDEPENDENT} PRIVATE /W4 /WX)
else ()
    target_compile_options(${INDEPENDENT} PRIVATE -Wall -Wextra -Wno-missing-field-initializers)
endif ()

## DESTINATION
set_target_properties(${INDEPENDENT} PROPERTIES RUNTIME_OUTPUT_DIRECTORY "..")

## LDD conan
target_link_libraries(${INDEPENDENT} PUBLIC ${CONAN_LIBS})


############## TESTS

include(CTest)
enable_testing()

##### WORKING TEST
#enable_testing()
#add_test(usage_test bin/client 1)
#set_tests_properties(usage_test PROPERTIES WILL_FAIL TRUE)

##### NOT WORKING TEST
#set(TEST_NUMBER 1)
#set(TEST noArg)
#add_test(NAME ${TEST}
#                           COMMAND ${CLIENT} 1)
#         COMMAND bin/server 1
#         COMMAND bin/client 1)
#set_tests_properties(${TEST} PROPERTIES WILL_FAIL FALSE)

set(TEST_NUMBER 1)
set(TEST noArg)
add_test(NAME ${TEST}
         COMMAND ${CMAKE_HOME_DIRECTORY}/infiniteCommands.sh -c ./bin/server 1 -c ./bin/client 1)
set_tests_properties(${TEST}
                     PROPERTIES
                     PASS_REGULAR_EXPRESSION "client connection, send, disconnection") ## todo change

## todo add new tests