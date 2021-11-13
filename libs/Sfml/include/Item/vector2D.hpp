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
        vector2D(int srcX, int srcY): x(srcX), y(srcY)
        {
        }
        ~vector2D() = default;

        bool operator==(const vector2D &b) const
        {
            return this->x == b.x && this->y == b.y;
        }

        bool operator!=(const vector2D &b) const
        {
            return !(*this == b);
        }

    public:
        int x;
        int y;
};

#endif