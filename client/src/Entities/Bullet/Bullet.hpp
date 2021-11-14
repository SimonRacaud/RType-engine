/*
** EPITECH PROJECT, 2021
** Bullet
** File description:
** Bullet.hpp
*/

#ifndef BULLET_HPP
#define BULLET_HPP

#include "Item/vector2D.hpp"

class Bullet
{
    public:
        Bullet(size_t charge, const vector2D &pos);
        Bullet(size_t charge, const vector2D &pos, const vector2D &velocity, const vector2D &size);
        ~Bullet() = default;
};

#endif