/*
** EPITECH PROJECT, 2021
** NetworkEventManager
** File description:
** NetworkEventManager.hpp
*/

#ifndef NETWORKEVENTMANAGER_HPP
#define NETWORKEVENTMANAGER_HPP

#include "Event/NetworkEvent/RoomListEventRefresh.hpp"
#include "Event/EventCallBackRegister/EventCallbackRegister.hpp"

class NetworkEventManager
{
	public:
        NetworkEventManager();
        ~NetworkEventManager() = default;

    private:
        static void refreshRoomList(const RoomListEventRefresh *e);
};

#endif