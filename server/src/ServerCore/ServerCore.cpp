/*
** EPITECH PROJECT, 2021
** ServerCore
** File description:
** ServerCore.cpp
*/

#include "ServerCore.hpp"

#include <iostream>
#include "global.hpp"
#include "CustomCluster.hpp"
#include "CustomEntityName.hpp"

Engine::IGameEngine &ServerCore::engine = Engine::EngineFactory::getInstance();
std::unique_ptr<ConfigFile> ServerCore::config = std::make_unique<ConfigFile>("server.config");

ServerCore::ServerCore()
{
}

ServerCore::~ServerCore()
{
}

void ServerCore::run(void)
{
}