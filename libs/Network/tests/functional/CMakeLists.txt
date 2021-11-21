##
## PERSONAL PROJECT, 2021
## R-Type Project
## File description:
## R-Type CMake
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
    ../../src/NetworkManager.cpp
    ../../src/DataWrapper.cpp
    ../../src/Tram/ComponentSync.cpp
    ../../src/Tram/CreateEntityReply.cpp
    ../../src/Tram/CreateEntityRequest.cpp
    ../../src/Tram/DestroyEntity.cpp
    ../../src/Tram/GetRoomList.cpp
    ../../src/Tram/Serializable.cpp
    ../../src/Tram/JoinCreateRoomReply.cpp
    ../../src/Tram/JoinRoom.cpp
    ../../src/Tram/TramBuffer.cpp
    ../../src/Tram/Serializable.cpp
    )

############## EXECUTABLES
####### Server
set(SERVER server)
set(SERVER_DIR ${SRC_DIR}${SERVER}/)

## SOURCES
set(SRCS_SERVER
    ${SERVER_DIR}testServerTCP.cpp
    ${SERVER_DIR}testServerTCPdataWrapper.cpp
    ${SERVER_DIR}testServerTCPnetworkManager.cpp
    ${SERVER_DIR}testServerUDP.cpp
    ${SERVER_DIR}testServerUDPdataWrapper.cpp
    ${SERVER_DIR}testServerUDPnetworkManager.cpp
    ${SERVER_DIR}testServerUDPdisconnection.cpp
    ${SERVER_DIR}testServerTCPdisconnection.cpp
    ${SERVER_DIR}testServerTCPresponse.cpp
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
    ${CLIENT_DIR}testClientTCPnetworkManager.cpp
    ${CLIENT_DIR}testClientUDP.cpp
    ${CLIENT_DIR}testClientUDPdataWrapper.cpp
    ${CLIENT_DIR}testClientUDPnetworkManager.cpp
    ${CLIENT_DIR}testClientUDPdisconnection.cpp
    ${CLIENT_DIR}testClientTCPdisconnection.cpp
    ${CLIENT_DIR}testClientTCPresponse.cpp
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
set(TEST_TIMEOUT 2)
include(CTest)
enable_testing()

set(CLIENT_TEST_BIN bin/client)
set(SERVER_TEST_BIN bin/server)
set(INDEPENDENT_TEST_BIN bin/independent)
set(SH_LAUNCH_SEVERAL_BIN ${CMAKE_HOME_DIRECTORY}/infiniteCommands.sh)
set(SH_ADD_CMD -c)

##### TEST THAT TESTS WORK
#add_test(TestTheTest bin/client 0)
#set_tests_properties(TestTheTest PROPERTIES WILL_FAIL FALSE)


## REAL TESTS
set(TEST_NB 1)
set(TEST simpleSendReceiveTCP)
add_test(NAME ${TEST}
         COMMAND ${SH_LAUNCH_SEVERAL_BIN} ${SH_ADD_CMD} ${SERVER_TEST_BIN} ${TEST_NB} ${SH_ADD_CMD} ${CLIENT_TEST_BIN}
         ${TEST_NB})
set_tests_properties(${TEST}
                     PROPERTIES WILL_FAIL FALSE
                     TIMEOUT ${TEST_TIMEOUT})


# TESTS IN LOOP

# TESTS TRAM BUFFER
set(TEST_NBS 2;3;4;5;6;7;8)

foreach (num IN ZIP_LISTS TEST_NBS)
    set(TEST_NB ${num_0})
    set(TEST test_TCP_dataWrapper_${TEST_NB})
    add_test(NAME ${TEST}
             COMMAND ${SH_LAUNCH_SEVERAL_BIN} ${SH_ADD_CMD} ${SERVER_TEST_BIN} ${TEST_NB} ${SH_ADD_CMD}
             ${CLIENT_TEST_BIN} ${TEST_NB})
    set_tests_properties(${TEST}
                         PROPERTIES WILL_FAIL FALSE
                         TIMEOUT ${TEST_TIMEOUT})

endforeach ()

set(TEST_NBS 9;10;11;12;13;14;15)

foreach (num IN ZIP_LISTS TEST_NBS)
    set(TEST_NB ${num_0})
    set(TEST test_TCP_networkManager_${TEST_NB})
    add_test(NAME ${TEST}
             COMMAND ${SH_LAUNCH_SEVERAL_BIN} ${SH_ADD_CMD} ${SERVER_TEST_BIN} ${TEST_NB} ${SH_ADD_CMD}
             ${CLIENT_TEST_BIN} ${TEST_NB})
    set_tests_properties(${TEST}
                         PROPERTIES WILL_FAIL FALSE
                         TIMEOUT ${TEST_TIMEOUT})
endforeach ()


set(TEST_NB 16)
set(TEST simpleSendReceiveUDP)
add_test(NAME ${TEST}
         COMMAND ${SH_LAUNCH_SEVERAL_BIN} ${SH_ADD_CMD} ${SERVER_TEST_BIN} ${TEST_NB} ${SH_ADD_CMD} ${CLIENT_TEST_BIN}
         ${TEST_NB})
set_tests_properties(${TEST}
                     PROPERTIES WILL_FAIL FALSE
                     TIMEOUT ${TEST_TIMEOUT})

set(TEST_NBS 17;18;19;20;21;22;23)

foreach (num IN ZIP_LISTS TEST_NBS)
    set(TEST_NB ${num_0})
    set(TEST test_UDP_dataWrapper_${TEST_NB})
    add_test(NAME ${TEST}
             COMMAND ${SH_LAUNCH_SEVERAL_BIN} ${SH_ADD_CMD} ${SERVER_TEST_BIN} ${TEST_NB} ${SH_ADD_CMD}
             ${CLIENT_TEST_BIN} ${TEST_NB})
    set_tests_properties(${TEST}
                         PROPERTIES WILL_FAIL FALSE
                         TIMEOUT ${TEST_TIMEOUT})
endforeach ()

set(TEST_NBS 24;25;26;27;28;29;30)

foreach (num IN ZIP_LISTS TEST_NBS)
    set(TEST_NB ${num_0})
    set(TEST test_UDP_networkManager_${TEST_NB})
    add_test(NAME ${TEST}
             COMMAND ${SH_LAUNCH_SEVERAL_BIN} ${SH_ADD_CMD} ${SERVER_TEST_BIN} ${TEST_NB} ${SH_ADD_CMD}
             ${CLIENT_TEST_BIN} ${TEST_NB})
    set_tests_properties(${TEST}
                         PROPERTIES WILL_FAIL FALSE
                         TIMEOUT ${TEST_TIMEOUT})
endforeach ()


set(TEST_NBS 31)

foreach (num IN ZIP_LISTS TEST_NBS)
    set(TEST_NB ${num_0})
    set(TEST test_UDP_disconnection_${TEST_NB})
    add_test(NAME ${TEST}
             COMMAND ${SH_LAUNCH_SEVERAL_BIN} ${SH_ADD_CMD} ${SERVER_TEST_BIN} ${TEST_NB} ${SH_ADD_CMD}
             ${CLIENT_TEST_BIN} ${TEST_NB})
    set_tests_properties(${TEST}
                         PROPERTIES WILL_FAIL FALSE
                         TIMEOUT ${TEST_TIMEOUT})
endforeach ()

set(TEST_NBS 32)

foreach (num IN ZIP_LISTS TEST_NBS)
    set(TEST_NB ${num_0})
    set(TEST test_TCP_disconnection_${TEST_NB})
    add_test(NAME ${TEST}
             COMMAND ${SH_LAUNCH_SEVERAL_BIN} ${SH_ADD_CMD} ${SERVER_TEST_BIN} ${TEST_NB} ${SH_ADD_CMD}
             ${CLIENT_TEST_BIN} ${TEST_NB})
    set_tests_properties(${TEST}
                         PROPERTIES WILL_FAIL FALSE
                         TIMEOUT ${TEST_TIMEOUT})
endforeach ()

set(TEST_NBS 33)

foreach (num IN ZIP_LISTS TEST_NBS)
    set(TEST_NB ${num_0})
    set(TEST test_TCP_response_${TEST_NB})
    add_test(NAME ${TEST}
             COMMAND ${SH_LAUNCH_SEVERAL_BIN} ${SH_ADD_CMD} ${SERVER_TEST_BIN} ${TEST_NB} ${SH_ADD_CMD}
             ${CLIENT_TEST_BIN} ${TEST_NB})
    set_tests_properties(${TEST}
                         PROPERTIES WILL_FAIL FALSE
                         TIMEOUT ${TEST_TIMEOUT})
endforeach ()

# TESTS TRAM BUFFER
set(TEST_NBS 1;2;3;4)
#
foreach (num IN ZIP_LISTS TEST_NBS)
    set(TEST_NB ${num_0})
    set(TEST test_tram_buffer_${TEST_NB})
    add_test(NAME ${TEST}
             COMMAND ${SH_LAUNCH_SEVERAL_BIN} ${SH_ADD_CMD} ${INDEPENDENT_TEST_BIN} ${TEST_NB})
    set_tests_properties(${TEST}
                         PROPERTIES WILL_FAIL FALSE
                         TIMEOUT ${TEST_TIMEOUT})
endforeach ()