/*
** EPITECH PROJECT , 2021
** GameRoomManager
** File description:
** GameRoomManager.hpp
*/

#ifndef GAMEROOMMANAGER_HPP
#define GAMEROOMMANAGER_HPP

#include "GameRoom/GameRoom.hpp"
#include <memory>

using std::unique_ptr;
using std::make_unique;

class GameRoomManager
{
    public:
        GameRoomManager();
        ~GameRoomManager();

        void createRoom(size_t roomId);
        void deleteRoom(size_t roomId);

        void createEntityEnemy(size_t roomId, uint32_t networkId);
        void destroyEntityEnemy(size_t roomId, uint32_t networkId);

    private:
        std::vector<unique_ptr<GameRoom>> _rooms;
};

#endif