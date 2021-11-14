/*
** EPITECH PROJECT, 2021
** ServerCore
** File description:
** ServerCore.cpp
*/

#include "ServerCore.hpp"

std::unique_ptr<ConfigFile> ServerCore::config = std::make_unique<ConfigFile>("server.config");

ServerCore::ServerCore() : _loop(true)
{
}

ServerCore::~ServerCore()
{
}

void ServerCore::run(void)
{
    while (_loop) {
        // TODO MAIN SERVER && DISPATCHER
    }
}