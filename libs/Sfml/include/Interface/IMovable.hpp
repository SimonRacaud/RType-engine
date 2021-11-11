/*
** PERSONAL PROJECT, 2021
** IMovable
** File description:
** IMovable.hpp
*/

#ifndef IMOVABLE_HPP
#define IMOVABLE_HPP

#include "Item/vector2D.hpp"
#include <string>

class IMovable
{
    public:
        ~IMovable() = default;

        virtual const vector2D &getPosition() = 0;
        virtual void setPosition(const vector2D &) = 0;
};

#endif