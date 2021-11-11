/*
** EPITECH PROJECT , 2021
** ScrollSystem
** File description:
** \file ScrollSystem.hpp
** \author simon
** \brief
** \date 11/11/2021
*/

#ifndef SCROLLSYSTEM_HPP
#define SCROLLSYSTEM_HPP

#include "EngineCore.hpp"

namespace System
{
    using std::vector;

    class ScrollSystem : public Engine::AbstractSystem<ScrollSystem> {
      public:
        ScrollSystem();
        virtual ~ScrollSystem() = default;

        virtual void run(const vector<Engine::Entity> &entities);
    };
}

#endif // SCROLLSYSTEM_HPP
