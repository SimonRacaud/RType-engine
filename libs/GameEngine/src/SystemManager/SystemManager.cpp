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
    for (auto &system : _selectedSystems) {
        system->run();
    }
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

std::vector<std::shared_ptr<IAbstractSystem>>::iterator SystemManager::retrieveSystem(const TypeIdx &type)
{
    auto sys = std::find_if(_systems.begin(), _systems.end(),
    [&](auto &sysType) {
        return sysType.getType() == type;
    });
    return sys;
}