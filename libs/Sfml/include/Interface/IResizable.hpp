/*
** PERSONAL PROJECT, 2021
** IResizable
** File description:
** IResizable.hpp
*/

#ifndef IRESIZABLE_HPP
#define IRESIZABLE_HPP

#include "Item/vector2D.hpp"
#include <string>

class IResizable
{
    public:
        ~IResizable() = default;

        virtual const vector2D &getSize() = 0;
        virtual void setSize(const vector2D &) = 0;
};

#endif