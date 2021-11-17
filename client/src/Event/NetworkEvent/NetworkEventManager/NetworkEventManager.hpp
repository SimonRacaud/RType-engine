/*
** EPITECH PROJECT, 2021
** NetworkEventManager
** File description:
** NetworkEventManager.hpp
*/

#ifndef NETWORKEVENTMANAGER_HPP
#define NETWORKEVENTMANAGER_HPP

#include "Event/NetworkEvent/NewGameEvent.hpp"
#include "Event/NetworkEvent/JoinRoomEvent.hpp"
#include "Event/NetworkEvent/RoomListEventRefresh.hpp"
#include "Event/EventCallBackRegister/EventCallbackRegister.hpp"

class NetworkEventManager
{
	public:
        NetworkEventManager();
        ~NetworkEventManager() = default;

    private:
        static void refreshRoomList(const RoomListEventRefresh *e);
        static void JoinRoom(const JoinRoomEvent *e);
        static void NewGame(const NewGameEvent *e);
};

#endif