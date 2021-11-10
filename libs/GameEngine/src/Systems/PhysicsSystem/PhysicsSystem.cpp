/*
** EPITECH PROJECT, 2021
** GameEngine
** File description:
** 27/05/2021 PhysicsSystem.cpp.cc
*/

#include "PhysicsSystem.hpp"
#include "FactoryShortcuts.hpp"

using namespace Engine;

static const Time refreshFreq = static_cast<Time>(1000);
static const SystemPriority priority = SystemPriority::HIGH;

PhysicsSystem::PhysicsSystem()
    : AbstractSystem<PhysicsSystem>(refreshFreq, priority)
{
    this->setRequirements<Position, Velocity>();
}

void PhysicsSystem::run(const std::vector<Engine::Entity> &entities)
{
    for (const Entity &entity : entities) {
        auto [position, velocity] = GET_COMP_M.getList<Position, Velocity>(entity);
        position.x += velocity.x;
        position.y += velocity.y;
    }
}
