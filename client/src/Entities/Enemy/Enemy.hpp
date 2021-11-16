/*
** EPITECH PROJECT, 2021
** Enemy
** File description:
** Enemy.hpp
*/

#ifndef ENEMY_HPP
#define ENEMY_HPP

#include "Item/vector2f.hpp"
#include "GameCore/GameCore.hpp"

class Enemy
{
    public:
        Enemy(Engine::ClusterName clusterName, const vector2D &pos, const vector2D &velocity, const vector2f &scale, const std::string &path, size_t nbStep, const surface &focus);
        ~Enemy() = default;

        void setNetworkId(uint32_t entityId);

    private:
        Engine::Entity _entity;
};

#endif