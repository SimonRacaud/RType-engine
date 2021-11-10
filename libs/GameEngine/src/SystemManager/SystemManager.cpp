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
        if (system->refresh()) {
            system->runSystem();
        }
    }
}

void SystemManager::_onEntityUpdated(Entity entity, const Signature &signature)
{
    for (auto &system : _systems) {
        system->onEntityUpdated(entity, signature);
    }
}

void SystemManager::_onEntityRemoved(Entity entity)
{
    for (shared_ptr<IAbstractSystem> system : _systems) {
        if (system != nullptr) {;
            system->onEntityRemoved(entity);
        }
    }
}

vector<shared_ptr<IAbstractSystem>>::iterator SystemManager::retrieveSystem(const TypeIdx &type)
{
    auto sys = std::find_if(_systems.begin(), _systems.end(),
        [type](shared_ptr<IAbstractSystem> &sysType) {
            return sysType->getType().hash_code() == type.hash_code();
    });
    return sys;
}