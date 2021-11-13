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
        GameRoomManager(GameRoom::ServerTypeTcp &tcp, GameRoom::ServerTypeUdp &udp);
        ~GameRoomManager();

        GameRoom::Id createRoom(GameRoom::PlayerList &);
        void deleteRoom(GameRoom::Id);

    private:
        GameRoom::Id _idReference;
        std::vector<GameRoom> _rooms;
        GameRoom::ServerTypeTcp &_tcp;
        GameRoom::ServerTypeUdp &_udp;
};

#endif