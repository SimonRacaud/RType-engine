/*
** EPITECH PROJECT, 2021
** GameEngine
** File description:
** 27/05/2021 Position.hpp.h
*/

#ifndef POSITION_HPP
#define POSITION_HPP

#include "BaseComponent/BaseComponent.hpp"

namespace Component
{
    struct Position : public Engine::BaseComponent<Position> {
        Position(float x, float y) : x(x), y(y) {}
        Position() = default;
        virtual ~Position() = default;

        float x{0};
        float y{0};
    };
} // namespace Engine

#endif // POSITION_HPP