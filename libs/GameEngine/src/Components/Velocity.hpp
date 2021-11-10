/*
** EPITECH PROJECT, 2021
** GameEngine
** File description:
** 27/05/2021 Velocity.hpp.h
*/

#ifndef VELOCITY_HPP
#define VELOCITY_HPP

#include "BaseComponent/BaseComponent.hpp"

namespace Engine
{
    struct Velocity : public BaseComponent<Velocity> {
        Velocity(float x, float y) : x(x), y(y) {}
        Velocity() = default;
        virtual ~Velocity() = default;

        float x{0};
        float y{0};
    };
} // namespace Engine

#endif // VELOCITY_HPP