/*
** EPITECH PROJECT, 2021
** GameEngine
** File description:
** 27/05/2021 Position.hpp.h
*/

#ifndef POSITION_HPP
#define POSITION_HPP

#include <cstring>
#include "BaseComponent/BaseComponent.hpp"

namespace Engine
{
    struct Position : public Engine::BaseComponent<Position> {
        Position(float x, float y) : x(x), y(y)
        {
        }
        explicit Position(void *buf)
        {
            memcpy((void *) this, buf, sizeof(Position));
        }
        Position() = default;
        ~Position() override = default;

        float x{0};
        float y{0};
    };
} // namespace Engine

#endif // POSITION_HPP