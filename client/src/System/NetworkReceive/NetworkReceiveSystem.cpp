/*
** EPITECH PROJECT , 2021
** NetworkReceiveSystem
** File description:
** \file NetworkReceiveSystem.cpp
** \author simon
** \brief
** \date 17/11/2021
*/

#include "NetworkReceiveSystem.hpp"
#include "GameCore/GameCore.hpp"

using namespace System;
using namespace Engine;
using namespace std;

static const Engine::Time freq = (Engine::Time)0;

NetworkReceiveSystem::NetworkReceiveSystem()
    : AbstractSystem<NetworkReceiveSystem>(freq, SystemPriority::HIGH)
{}

void NetworkReceiveSystem::run(const vector<Entity> &)
{
    GameCore::networkCore.receive();
}
