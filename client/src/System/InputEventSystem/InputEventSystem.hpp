/*
** EPITECH PROJECT , 2021
** InputEventSystem
** File description:
** InputEventSystem.hpp
*/

#ifndef IPUTEVENTSYSTEM_HPP
#define IPUTEVENTSYSTEM_HPP

#include "EngineCore.hpp"

namespace System
{
    class InputEventSystem : public Engine::AbstractSystem<InputEventSystem>
    {
        public:
            InputEventSystem();

            void run(const std::vector<Engine::Entity> &entities);
    };
}

#endif