/*
** EPITECH PROJECT, 2021
** RoomListEventManager
** File description:
** RoomListEventManager.cpp
*/

#include "GameCore/GameCore.hpp"
#include "RoomListEventManager.hpp"
#include "EngineCore.hpp"

RoomListEventManager::RoomListEventManager()
{
    Engine::Event::EventCallbackRegister &reg = Engine::EngineFactory::getInstance().getEventRegister();
    reg.registerCallback<RoomListEventRefresh>(RoomListEventManager::refreshRoomList);
}

void RoomListEventManager::refreshRoomList(const RoomListEventRefresh *)
{
    GameCore::networkCore.getRoomList();
}