/*
** EPITECH PROJECT , 2021
** GameRoom
** File description:
** GameRoom.hpp
*/

#ifndef GAMEROOM_HPP
#define GAMEROOM_HPP

#include <thread>
#include <vector>
#include <cstddef>

#include "AsioServerTCP.hpp"
#include "AsioConnectionUDP.hpp"

class GameRoom
{
    public:
        using Id = size_t;
        using PlayerList = std::vector<int>;    // TODO CHANGE JUSt UNKNOWN FOR THE MOMENT
        using ServerTypeTcp = int;              // Network::AsioServerTCP<1>;
        using ServerTypeUdp = int;              // Network::AsioConnectionUDP<1>;

    public:
        GameRoom(PlayerList &player, Id id, ServerTypeTcp tcp, ServerTypeUdp udp);
        GameRoom(const GameRoom &);
        ~GameRoom();

        Id getId() const;

        void create();
        void run();
        void destroy();

        GameRoom &operator=(const GameRoom &);

    private:
        void waitConnection();

    private:
        Id _id;
        PlayerList _playerList;
        ServerTypeTcp _tcp;
        ServerTypeUdp _udp;
        std::thread _thread;
};

#endif