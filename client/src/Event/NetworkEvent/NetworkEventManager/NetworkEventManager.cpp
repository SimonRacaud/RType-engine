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
}

void NetworkEventManager::refreshRoomList(const RoomListEventRefresh *)
{
    GameCore::networkCore.getRoomList();
}