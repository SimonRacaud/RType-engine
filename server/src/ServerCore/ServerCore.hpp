/*
** EPITECH PROJECT, 2021
** ServerCore
** File description:
** ServerCore.hpp
*/

#ifndef SERVERCORE_HPP
#define SERVERCORE_HPP

#include <memory>
#include "ConfigFile.hpp"
#include "GameRoomManager/GameRoomManager.hpp"
#include "ServerNetworkCore/ServerNetworkCore.hpp"

class ServerCore
{
    public:
        ServerCore();
        ServerCore(const ServerCore &) = delete;
        ~ServerCore();

        void run(void);

    private:
        bool _loop;
        GameRoomManager _rooms;

    public:
        static std::unique_ptr<ConfigFile> config;
        static std::unique_ptr<IServerNetworkCore> network;
};

#endif