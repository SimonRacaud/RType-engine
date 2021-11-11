/*
** EPITECH PROJECT, 2021
** GameEngine
** File description:
** 27/05/2021 IComponentTypeRegister.hpp.h
*/

#ifndef ICOMPONENTTYPEREGISTER_HPP
#define ICOMPONENTTYPEREGISTER_HPP

#include <cstddef>
#include "global.hpp"

namespace Engine
{
    class IComponentTypeRegister {
      public:
        virtual ~IComponentTypeRegister() = default;

        virtual void allocate(std::size_t size) = 0;
        virtual void remove(Entity entity) = 0;
    };
} // namespace Engine

#endif // ICOMPONENTTYPEREGISTER_HPP