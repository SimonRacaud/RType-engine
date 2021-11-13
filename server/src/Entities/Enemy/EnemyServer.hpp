/*
** EPITECH PROJECT, 2021
** EnemyServer
** File description:
** EnemyServer.hpp
*/

#ifndef ENEMYSERVER_HPP
#define ENEMYSERVER_HPP

#include "Item/vector2D.hpp"

#include "Components/Position.hpp"
#include "Components/Velocity.hpp"

class EnemyServer
{
    public:
        EnemyServer(Engine::ClusterName clusterName, const vector2D &pos, const vector2D &velocity);
        ~EnemyServer() = default;
};

#endif