/*
** EPITECH PROJECT, 2021
** Bullet
** File description:
** Bullet.hpp
*/

#ifndef BULLET_HPP
#define BULLET_HPP

#include "Item/vector2D.hpp"
#include "CustomCluster.hpp"
#include "GameCore/GameCore.hpp"

using Engine::ClusterName;

class Bullet
{
    public:
        Bullet(ClusterName cluster, size_t charge, const vector2D &pos);
        Bullet(ClusterName cluster, size_t charge, const vector2D &pos, const vector2D &velocity);
        ~Bullet() = default;

        void setNetworkId(uint32_t entityId);

    private:
        Engine::Entity _entity;
};

#endif