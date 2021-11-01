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
#include "env.hpp"

namespace Engine
{
    using Entity = uint32_t;

    using Index = uint32_t;

    static constexpr auto InvalidIndex = std::numeric_limits<Index>::max();

    typedef std::bitset<MAX_COMPONENT_TYPE> Signature;
}

#endif // GLOBAL_HPP
