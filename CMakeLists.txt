##
## EPITECH PROJECT, 2021
## R-Type
## File description:
## C++ Program
##

cmake_minimum_required(VERSION 3.17)

set(CONAN_DISABLE_CHECK_COMPILER True)

set(CMAKE_BUILD_TYPE Debug)
#set(CMAKE_BUILD_TYPE Release)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(NAME_CLIENT r-type_client)
set(NAME_SERVER r-type_server)

project(${NAME_CLIENT} VERSION 0.1 LANGUAGES CXX)
project(${NAME_SERVER} VERSION 0.1 LANGUAGES CXX)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

## GLOBAL INCLUDES
include_directories(./include)
include_directories(./common/include)
include_directories(./server/src/DLLoader)

##
## COMMON
##
## SOURCES
set(COMMON_SRCS
    common/src/Network/Tram/ComponentSync.cpp
    common/src/Network/Tram/CreateEntityReply.cpp
    common/src/Network/Tram/CreateEntityRequest.cpp
    common/src/Network/Tram/DestroyEntity.cpp
    common/src/Network/Tram/EndGame.cpp
    common/src/Network/Tram/GetRoomList.cpp
    common/src/Network/Tram/JoinCreateRoomReply.cpp
    common/src/Network/Tram/JoinRoom.cpp
    common/src/Network/Tram/TramBuffer.cpp
    common/src/Network/Serializable.cpp
    common/src/Network/NetworkManager.cpp
    )

##
## CLIENT
##
## SOURCES
set(CLIENT_SRCS
    client/src/main.cpp
    client/src/ConfigFileExternal/ConfigFileExternal.cpp
    client/src/Scene/Start/StartScene.cpp

    client/src/System/RenderSystem/RenderSystem.cpp
    client/src/System/LogPosition/LogPositionSystem.cpp
    client/src/System/SyncSendSystem/SyncSendSystem.cpp
    client/src/System/InputEventSystem/InputEventSystem.cpp
    client/src/System/PhysicsSystem/PhysicsSystem.cpp
    client/src/System/TimerSystem/TimerSystem.cpp
    client/src/System/ColliderSystem/ColliderSystem.cpp

    client/src/Event/AudioEvent/AudioEventManager/AudioEventManager.cpp
    client/src/Event/EmptyCluster/EmptyClusterManager/EmptyClusterManager.cpp
    client/src/Event/MoveEvents/MoveHandler/MoveHandler.cpp
    client/src/Event/ShootEvents/ShootEventsManager/ShootEventsManager.cpp
    client/src/Event/NetworkEvent/NetworkEventManager/NetworkEventManager.cpp
    client/src/Event/ExplosionEvents/ExplosionEventsManager/ExplosionEventsManager.cpp
    client/src/Event/EntityRemove/EntityRemoveManager/EntityRemoveManager.cpp
    client/src/Event/EntityHit/EntityHitManager/EntityHitManager.cpp
    client/src/Event/AddScore/AddScoreEventManager/AddScoreEventManager.cpp
    client/src/Scene/Debug/DebugScene.cpp
    client/src/GameCore/GameCore.cpp
    client/src/EntityFactory/EntityFactory.cpp

    client/src/Entities/Button/Button.cpp
    client/src/Entities/Player/Player.cpp
    client/src/Entities/Enemy/Enemy.cpp
    client/src/Entities/Bullet/Bullet.cpp
    client/src/Entities/Explosion/Explosion.cpp
    client/src/Entities/ScrollingBackground/ScrollingBackground.cpp

    client/src/Component/Scroll.hpp
    client/src/System/ScrollSystem/ScrollSystem.cpp
    client/src/Scene/Home/HomeScene.cpp
    client/src/Scene/Settings/SettingsScene.cpp
    client/src/Scene/Game/GameScene.cpp
    client/src/Scene/RoomList/RoomListScene.cpp
    client/src/Entities/ImageView/ImageView.cpp
    client/src/Entities/Label/Label.cpp
    client/src/Entities/Progress/ProgressBar.cpp
    client/src/Event/GUI/GuiEventManager.cpp
    client/src/Entities/Equipment/Equipment.cpp
    client/src/Util/MathLerp.cpp
    client/src/ClientNetworkCore/ClientNetworkCore.cpp
    client/src/System/NetworkReceive/NetworkReceiveSystem.cpp
    client/src/System/OutofBoundsSystem/OutofBoundsSystem.cpp
    client/src/Rollback/ComponentRollback.cpp
    client/src/Scene/EndGame/EndGameScene.cpp
    client/src/System/ScoreSystem/ScoreSystem.cpp
    ${COMMON_SRCS}
    )
add_executable(${NAME_CLIENT} ${CLIENT_SRCS})

target_include_directories(${NAME_CLIENT} PUBLIC client/src client/include)

if (WIN32)
    target_compile_options(${NAME_CLIENT} PRIVATE)
else ()
    target_compile_options(${NAME_CLIENT} PRIVATE -g -Wall -Wextra -Wno-missing-field-initializers)
endif ()

set_target_properties(${NAME_CLIENT}
                      PROPERTIES
                      RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}"
                      )
##
## SERVER
##
## SOURCES
set(SERVER_SRCS
    ./server/src/main.cpp
    ./server/src/GameStage/GameStage.cpp
    ./server/src/DLLoader/DLLoader.hpp
    ./server/src/ServerCore/ServerCore.cpp
    ./server/src/ServerCore/ConfigFileExternal/ConfigFileExternal.cpp
    ./server/src/EnemyLoader/EnemyLoader.cpp
    ./server/src/StateMachine/StateMachine.cpp
    ./server/src/GameRoomManager/GameRoomManager.cpp
    ./server/src/GameRoomManager/GameRoom/GameRoom.cpp

    server/src/ServerNetworkCore/ServerNetworkCore.cpp
    server/src/GarbageEntity/GarbageEntity.cpp
    server/src/StateMachineManager/StateMachineManager.cpp
    server/src/PhysicController/PhysicController.cpp
    ${COMMON_SRCS}
    )

add_executable(${NAME_SERVER} ${SERVER_SRCS})

target_include_directories(${NAME_SERVER} PUBLIC server/src server/include libs/Network)

if (MSVC)
    set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS TRUE)
    set(BUILD_SHARED_LIBS TRUE)
endif ()

if (WIN32)
    set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreadedDLL")
    target_compile_options(${NAME_SERVER} PRIVATE)
else ()
    target_compile_options(${NAME_SERVER} PRIVATE -Wall -Wextra -Wno-missing-field-initializers)
endif ()

set_target_properties(${NAME_SERVER}
                      PROPERTIES
                      RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}"
                      )

target_link_libraries(${NAME_SERVER} ${CMAKE_DL_LIBS})

## GAME-ENGINE (client & server)
set(GAME_ENGINE_DIR ${PROJECT_SOURCE_DIR}/libs/GameEngine)
add_subdirectory(${PROJECT_SOURCE_DIR}/libs/GameEngine/)
include_directories(${GAME_ENGINE_DIR}/include ${GAME_ENGINE_DIR}/src)
target_link_libraries(${NAME_CLIENT} gameEngine)
target_link_libraries(${NAME_SERVER} gameEngine)

## Network
set(NetworkDir ${PROJECT_SOURCE_DIR}/libs/Network)
add_subdirectory(${NetworkDir})
include_directories(${NetworkDir}/include)
target_link_libraries(${NAME_CLIENT} Network)
target_link_libraries(${NAME_SERVER} Network)

## CONFIG_FILE (client & server)
set(ConfigFileDir ${PROJECT_SOURCE_DIR}/libs/ConfigFile)
add_subdirectory(${ConfigFileDir})
include_directories(${ConfigFileDir}/include)
include_directories(${ConfigFileDir}/src/ConfigFileTools)
target_link_libraries(${NAME_CLIENT} ConfigFile)
target_link_libraries(${NAME_SERVER} ConfigFile)

## SFML (client)
set(SfmlDir ${PROJECT_SOURCE_DIR}/libs/Sfml)
add_subdirectory(${SfmlDir})
include_directories(${SfmlDir}/include)
include_directories(${SfmlDir}/src)
target_link_libraries(${NAME_CLIENT} Sfml)

## Enemy Lib
set(EnemyDir ${PROJECT_SOURCE_DIR}/libs/Enemies)

## PataPata Lib
add_subdirectory(${EnemyDir}/PataPata)
include_directories(${EnemyDir}/PataPata)
target_link_libraries(${NAME_SERVER} PataPata)
## Cancer Lib
add_subdirectory(${EnemyDir}/Cancer)
include_directories(${EnemyDir}/Cancer)
target_link_libraries(${NAME_SERVER} Cancer)