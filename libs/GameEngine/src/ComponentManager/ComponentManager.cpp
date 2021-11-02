/*
** EPITECH PROJECT , 2021
** ComponentManager
** File description:
** simon
*/

#include "ComponentManager.hpp"

using namespace Engine;

ComponentManager::ComponentManager()
{
    this->allocate();
}

void ComponentManager::allocate()
{
    for (std::size_t i = 0; i < MAX_COMPONENT_TYPE; i++) {
        if (_componentRegisters[i]) {
            _componentRegisters[i]->allocate(ALLOC_COMPONENT_INSTANCE);
        }
    }
}