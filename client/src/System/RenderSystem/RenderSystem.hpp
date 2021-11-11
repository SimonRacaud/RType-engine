/*
** EPITECH PROJECT , 2021
** RenderSystem
** File description:
** RenderSystem.hpp
*/

#ifndef RENDERSYSTEM_HPP
#define RENDERSYSTEM_HPP

#include "EngineCore.hpp"

namespace System
{
    class RenderSystem : public Engine::AbstractSystem<RenderSystem>
    {
        public:
            RenderSystem();

            void run(const std::vector<Engine::Entity> &entities);
    };
}

#endif