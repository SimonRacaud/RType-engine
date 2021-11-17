/*
** EPITECH PROJECT, 2021
** NetworkEventManager
** File description:
** NetworkEventManager.cpp
*/

#include "GameCore/GameCore.hpp"
#include "NetworkEventManager.hpp"
#include "EngineCore.hpp"

NetworkEventManager::NetworkEventManager()
{
    Engine::Event::EventCallbackRegister &reg = Engine::EngineFactory::getInstance().getEventRegister();
    reg.registerCallback<RoomListEventRefresh>(NetworkEventManager::refreshRoomList);
    reg.registerCallback<NewGameEvent>(NetworkEventManager::NewGame);
}

void NetworkEventManager::refreshRoomList(const RoomListEventRefresh *)
{
    GameCore::networkCore.getRoomList();
}

void NetworkEventManager::NewGame(const NewGameEvent *)
{
    GameCore::networkCore.createRoom();
}