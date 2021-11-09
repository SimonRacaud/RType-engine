/*
** PERSONAL PROJECT, 2021
** vector2D
** File description:
** vector2D.hpp
*/

#ifndef VECTOR2D_HPP
#define VECTOR2D_HPP

#include <iostream>

class vector2D
{
    public:
        vector2D(): x(0), y(0)
        {
        }
        vector2D(const vector2D &src): x(src.x), y(src.y)
        {
        }
        vector2D(size_t srcX, size_t srcY): x(srcX), y(srcY)
        {
        }
        ~vector2D() = default;

    public:
        size_t x;
        size_t y;
};

#endif