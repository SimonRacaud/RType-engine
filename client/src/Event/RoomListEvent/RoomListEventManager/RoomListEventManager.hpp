/*
** EPITECH PROJECT, 2021
** RoomListEventManager
** File description:
** RoomListEventManager.hpp
*/

#ifndef ROOMLISTEVENTMANAGER_HPP
#define ROOMLISTEVENTMANAGER_HPP

#include "Event/RoomListEvent/RoomListEventRefresh.hpp"
#include "Event/EventCallBackRegister/EventCallbackRegister.hpp"

class RoomListEventManager
{
	public:
        RoomListEventManager();
        ~RoomListEventManager() = default;

    private:
        static void refreshRoomList(const RoomListEventRefresh *e);
};

#endif