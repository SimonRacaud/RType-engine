/*
** EPITECH PROJECT, 2021
** GameEngine
** File description:
**
*/

#ifndef ENTITY_NAME_HPP
#define ENTITY_NAME_HPP

#include <cstddef>

namespace Engine
{
    enum class EntityName : std::size_t {
        EMPTY = 0,

        #ifdef CUSTOM_ENTITY_NAME
                CUSTOM_ENTITY_NAME
        #endif
    };
}

#endif // ENTITY_NAME_HPP
