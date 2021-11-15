/*
** EPITECH PROJECT, 2021
** Explosion
** File description:
** Explosion.hpp
*/

#ifndef EXPLOSION_HPP
#define EXPLOSION_HPP

#include "Item/vector2D.hpp"
#include "CustomCluster.hpp"

using Engine::ClusterName;

class Explosion
{
    public:
        Explosion(const vector2D &pos);
        ~Explosion() = default;
};

#endif