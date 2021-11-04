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
    struct Velocity : public Component<Velocity> {
        Velocity(float x, float y) : x(x), y(y)
        {
        }
        Velocity() : x(0), y(0)
        {
        }

        virtual ~Velocity() = default;

        float x;
        float y;
    };
} // namespace Engine

#endif // VELOCITY_HPP