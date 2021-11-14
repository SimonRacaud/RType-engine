/*
** EPITECH PROJECT , 2021
** GameRoomManager
** File description:
** GameRoomManager.hpp
*/

#ifndef GAMEROOMMANAGER_HPP
#define GAMEROOMMANAGER_HPP

#include "GameRoom/GameRoom.hpp"
#include "PortManager/PortManager.hpp"

class GameRoomManager
{
    public:
        GameRoomManager(int, int);
        ~GameRoomManager();

        GameRoom::Id createRoom(GameRoom::PlayerList &);
        void deleteRoom(GameRoom::Id);

    private:
        GameRoom::Id _idReference;
        std::vector<GameRoom> _rooms;
        PortManager _port;
};

#endif