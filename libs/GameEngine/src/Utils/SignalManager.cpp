/*
** EPITECH PROJECT , 2021
** SignalManager
** File description:
** \file SignalManager.cpp
** \author simon
** \brief
** \date 08/11/2021
*/

#include "SignalManager.hpp"
#include <csignal>
#include "Engine/EngineFactory.hpp"

using namespace Engine;

void SignalManager::apply()
{
    signal(SIGINT, handler);
}

void SignalManager::handler(int)
{
    std::cout << "CTRL+C detected, exit engine..." << std::endl;
    EngineFactory::getInstance().quit();
}