/*
** PERSONAL PROJECT, 2021
** surface
** File description:
** surface.hpp
*/

#ifndef SURFACE_HPP
#define SURFACE_HPP

#include "vector2D.hpp"

class surface
{
    public:
        surface(): pos(), size()
        {
        }
        surface(const surface &src): pos(src.pos), size(src.size)
        {
        }
        surface(const vector2D &srcPos, const vector2D &srcSize): pos(srcPos), size(srcSize)
        {
        }
        ~surface() = default;

    public:
        vector2D pos;
        vector2D size;
};

#endif