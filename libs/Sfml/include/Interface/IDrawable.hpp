/*
** PERSONAL PROJECT, 2021
** IDrawable
** File description:
** IDrawable.hpp
*/

#ifndef IDRAWABLE_HPP
#define IDRAWABLE_HPP

#include "IMovable.hpp"

template <typename renderTool>
class IDrawable : public IMovable
{
    public:
        ~IDrawable() = default;

        virtual void refresh() = 0;
        virtual void draw() = 0;
};

#endif