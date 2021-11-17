/*
** EPITECH PROJECT, 2021
** ServerCore
** File description:
** ServerCore.cpp
*/

#include "ServerCore.hpp"
#include "ConfigFileExternal/ConfigFileExternal.hpp"

std::unique_ptr<ConfigFile> ServerCore::config = std::make_unique<ConfigFile>("server.config");

ServerCore::ServerCore() :
_loop(true),
_rooms()
{
    config->setVarGetter<std::pair<int, int>>(ConfigFileExternal::getPairIntInt);

    // TODO create TCP server with port var
}

ServerCore::~ServerCore()
{
    // TODO close TCP server
}

void ServerCore::run(void)
{
    while (_loop) {
        // TODO MAIN SERVER && DISPATCHER
    }
}