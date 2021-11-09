/*
** EPITECH PROJECT , 2021
** LogPositionSystem
** File description:
** \file LogPositionSystem.hpp
** \author simon
** \brief
** \date 04/11/2021
*/

#ifndef LOGPOSITIONSYSTEM_HPP
#define LOGPOSITIONSYSTEM_HPP

#include "EngineCore.hpp"

namespace System
{
    using std::vector;

    class LogPositionSystem
        : public Engine::AbstractSystem<LogPositionSystem> {
      public:
        LogPositionSystem();

        virtual void run(const vector<Engine::Entity> &entities);
    };
} // namespace System

#endif // LOGPOSITIONSYSTEM_HPP
