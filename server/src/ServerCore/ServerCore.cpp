/*
** EPITECH PROJECT, 2021
** ServerCore
** File description:
** ServerCore.cpp
*/

#include "ServerCore.hpp"
#include "ConfigFileExternal/ConfigFileExternal.hpp"

std::unique_ptr<ConfigFile> ServerCore::config = std::make_unique<ConfigFile>("server.config");
std::unique_ptr<IServerNetworkCore> ServerCore::network = nullptr;

ServerCore::ServerCore() :
_loop(true),
_rooms()
{
    config->setVarGetter<std::pair<int, int>>(ConfigFileExternal::getPairIntInt);
    if (!network)
        network = std::make_unique<ServerNetworkCore>();
}

ServerCore::~ServerCore()
{
}

void ServerCore::run(void)
{
    network->receiveLoop();
}