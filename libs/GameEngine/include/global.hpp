/*
** EPITECH PROJECT, 2021
** GameEngine
** File description:
** 27/05/2021 entity.hpp.h
*/

#ifndef GLOBAL_HPP
#define GLOBAL_HPP

#include <cstdint>
#include <limits>
#include <bitset>
#include <typeindex>
#include <functional>
#include "env.hpp"
#include "EntityName.hpp"
#include "ClusterName.hpp"

namespace Engine
{
    using Entity = uint32_t;

    using Index = uint32_t;

    using TypeIdx = std::type_index;

    using NetworkId = uint32_t;

    using EntityDestructor = std::function<void(Entity, EntityName, ClusterName)>;

    static constexpr Entity MaxEntity = std::numeric_limits<Entity>::max();
    static constexpr Index InvalidIndex = std::numeric_limits<Index>::max();

    typedef std::bitset<MAX_COMPONENT_TYPE> Signature;
}

#endif // GLOBAL_HPP
