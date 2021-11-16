/*
** EPITECH PROJECT, 2021
** ComponentRollback.cpp
** File description:
** TODO: add description
*/
#include "ComponentRollback.hpp"

const std::unordered_map<std::size_t, std::function<void(Engine::Entity, void *, long int)>>
    ComponentRollback::hashcodeComponents{{Engine::Position::type.hash_code(), ComponentRollback::RollbackPosition}};

void ComponentRollback::Apply(Engine::Entity id, size_t componentTypeHash, void *component, long timestamp)
{
    if (hashcodeComponents.contains(componentTypeHash))
        hashcodeComponents.at(componentTypeHash)(id, component, timestamp);
}

void ComponentRollback::RollbackPosition(Engine::Entity id, void *component, long int timestamp)
{
    auto actPosComp(GET_COMP_M.get<Engine::Position>(id));
    const auto actVelComp(GET_COMP_M.get<Engine::Velocity>(id));
    Engine::Position recvPos(component);

    recvPos.x += (actVelComp.x * (float) timestamp);
    recvPos.y += (actVelComp.y * (float) timestamp);

    actPosComp.x = recvPos.x;
    actPosComp.y = recvPos.y;
}