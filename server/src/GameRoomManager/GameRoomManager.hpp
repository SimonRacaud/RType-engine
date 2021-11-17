/*
** EPITECH PROJECT , 2021
** GameRoomManager
** File description:
** GameRoomManager.hpp
*/

#ifndef GAMEROOMMANAGER_HPP
#define GAMEROOMMANAGER_HPP

#include "GameRoom/GameRoom.hpp"

class GameRoomManager
{
    public:
        GameRoomManager();
        ~GameRoomManager();

        void createRoom(size_t roomId);
        void deleteRoom(size_t roomId);

    private:
        std::vector<GameRoom> _rooms;
};

#endif