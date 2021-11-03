/*
** PERSONAL PROJECT, 2021
** IDrawable
** File description:
** IDrawable.hpp
*/

#ifndef IDRAWABLE_HPP
#define IDRAWABLE_HPP

template <typename renderTool>
class IDrawable
{
    public:
        ~IDrawable() = default;

        virtual void draw(renderTool &render) = 0;
};

#endif