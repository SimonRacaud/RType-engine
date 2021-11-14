/*
** EPITECH PROJECT, 2021
** ServerCore
** File description:
** ServerCore.cpp
*/

#include "ServerCore.hpp"

std::unique_ptr<ConfigFile> ServerCore::config = std::make_unique<ConfigFile>("server.config");

ServerCore::ServerCore() :
_loop(true),
_rooms(ServerCore::config->getVar<int>("PORT_PAGE_START"), ServerCore::config->getVar<int>("PORT_PAGE_END"))
{
    int port = config->getVar<int>("PORT_MAIN_SERVER");

    (void) port;
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