/*
** EPITECH PROJECT , 2021
** NetworkReceiveSystem
** File description:
** \file NetworkReceiveSystem.hpp
** \author simon
** \brief
** \date 17/11/2021
*/

#ifndef NETWORKRECEIVESYSTEM_HPP
#define NETWORKRECEIVESYSTEM_HPP

#include "EngineCore.hpp"
#include <vector>

namespace System
{
    class NetworkReceiveSystem : public Engine::AbstractSystem<NetworkReceiveSystem> {
      public:
        NetworkReceiveSystem();

        virtual void run(const std::vector<Engine::Entity> &entities);
    };
}

#endif // NETWORKRECEIVESYSTEM_HPP
