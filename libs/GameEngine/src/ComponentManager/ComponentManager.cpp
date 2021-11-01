/*
** EPITECH PROJECT , 2021
** ComponentManager
** File description:
** simon
*/

#include "ComponentManager.hpp"

using namespace Engine;

void ComponentManager::allocate(std::size_t size)
{
    for (std::size_t i = 0; i < MAX_COMPONENT_TYPE; i++) {
        if (_componentRegisters[i]) {
            _componentRegisters[i]->allocate(ALLOC_COMPONENT);
        }
    }
}
