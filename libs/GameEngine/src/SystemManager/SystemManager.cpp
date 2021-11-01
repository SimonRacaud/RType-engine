/*
** EPITECH PROJECT, 2021
** GameEngine
** File description:
** 31/05/2021 SystemManager.cpp.c
*/

#include "SystemManager.hpp"

using namespace Engine;

void SystemManager::executeCycle()
{
    // TODO
}

void SystemManager::onEntityUpdated(Entity entity, const Signature &signature)
{
    for (auto &system : _systems) {
        system->onEntityUpdated(entity, signature);
    }
}

void SystemManager::onEntityRemoved(Entity entity)
{
    for (auto &system : _systems) {
        system->onEntityRemoved(entity);
    }
}