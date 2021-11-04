/*
** EPITECH PROJECT, 2021
** GameEngine
** File description:
** 27/05/2021 PhysicsSystem.hpp.h
*/

#ifndef PHYSICSSYSTEM_HPP
#define PHYSICSSYSTEM_HPP

#include "env.hpp"
#include "global.hpp"
#include "AbstractSystem/AbstractSystem.hpp"
#include "Components/Position.hpp"
#include "Components/Velocity.hpp"
#include "EntityManager/EntityManager.hpp"

namespace Engine
{
    class PhysicsSystem : public AbstractSystem<PhysicsSystem> {
      public:
        PhysicsSystem();
        virtual ~PhysicsSystem() = default;

        void run();

      private:
    };
}

#endif // PHYSICSSYSTEM_HPP