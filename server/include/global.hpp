/*
** EPITECH PROJECT , 2021
** global
** File description:
** \file global.hpp
** \author simon
** \brief
** \date 15/11/2021
*/

#ifndef GLOBAL_HPP
#define GLOBAL_HPP

#include <inttypes.h>
#include <typeindex>

using Entity = uint32_t;
using NetworkId = uint32_t;

using Index = uint32_t;
using TypeIdx = std::type_index;
static constexpr Index InvalidIndex = std::numeric_limits<Index>::max();
#define GET_TYPE_IDX(type) std::type_index(typeid(type))

#endif // GLOBAL_HPP
