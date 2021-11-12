/*
** PERSONAL PROJECT, 2021
** vector2F
** File description:
** vector2F.hpp
*/

#ifndef VECTOR2F_HPP
#define VECTOR2F_HPP

#include <iostream>

class vector2f
{
    public:
      vector2f(): x(0), y(0)
        {
        }
        vector2f(const vector2f &src): x(src.x), y(src.y)
        {
        }
        vector2f(float srcX, float srcY): x(srcX), y(srcY)
        {
        }
        ~vector2f() = default;

        bool operator==(const vector2f &b) const
        {
            return this->x == b.x && this->y == b.y;
        }

        bool operator!=(const vector2f &b) const
        {
            return !(*this == b);
        }

    public:
        float x;
        float y;
};

#endif