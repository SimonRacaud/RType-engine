/*
** EPITECH PROJECT, 2021
** ComponentRollback.cpp
** File description:
** TODO: add description
*/

#include "ComponentRollback.hpp"

/**
 * @brief Refresh rate of the physic system in milliseconds
 */
static const float PhysicSystemRefreshRate = 10;

const std::unordered_map<std::size_t, std::function<void(Engine::Entity, void *, long int)>>
    ComponentRollback::hashcodeComponents{
        {Engine::Position::type.hash_code(), ComponentRollback::RollbackPosition}
    };

void ComponentRollback::Apply(Tram::ComponentSync const &tram)
{
    const Engine::Entity entity = GET_ENTITY_M.getId(tram.networkId);

    if (hashcodeComponents.contains(tram.componentType)) {
        hashcodeComponents.at(tram.componentType)(entity, tram.component, tram.timestamp);
    }
}

void ComponentRollback::RollbackPosition(Engine::Entity id, void *component, long int timestamp)
{
    auto &oldComponent = GET_COMP_M.get<Engine::Position>(id);
    const auto &velocity = GET_COMP_M.get<Engine::Velocity>(id);
    const Engine::Position *newComponent = reinterpret_cast<Engine::Position *>(component);
    float deltaTime = (GET_NOW - timestamp);
    float numberMissingCycle = (deltaTime / PhysicSystemRefreshRate);

    oldComponent.x = newComponent->x + (velocity.x * numberMissingCycle);
    oldComponent.y = newComponent->y + (velocity.y * numberMissingCycle);
}