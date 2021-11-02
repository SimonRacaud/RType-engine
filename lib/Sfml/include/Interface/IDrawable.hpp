/*
** PERSONAL PROJECT, 2021
** IDrawable
** File description:
** IDrawable.hpp
*/

#ifndef IDRAWABLE_HPP
#define IDRAWABLE_HPP

class IDrawable
{
    public:
        ~IDrawable() = default;

        virtual void draw(/*???*/) = 0;
};

#endif