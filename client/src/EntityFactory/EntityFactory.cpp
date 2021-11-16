/*
** EPITECH PROJECT, 2021
** EntityFactory
** File description:
** EntityFactory.cpp
*/

#include <stdexcept>
#include "EntityFactory.hpp"

#include "Entities/Enemy/Enemy.hpp"
#include "Entities/Bullet/Bullet.hpp"
#include "Entities/Player/Player.hpp"
#include "Entities/Explosion/Explosion.hpp"
#include "Entities/Equipment/Equipment.hpp"

EntityFactory::EntityFactory(Engine::ClusterName clusterName) : _clusterName(clusterName)
{
}

void EntityFactory::build(const std::string &entityType, uint32_t entityId)
{
    try {
        this->_factory.at(entityType)(_clusterName, entityId);
    } catch (...) {
        throw std::invalid_argument("EntityFactory build failed");
    }
}

void EntityFactory::makeEnemy(Engine::ClusterName clusterName, uint32_t entityId)
{
    Enemy(clusterName, vector2D(0, 0), vector2D(0, 0), vector2f(1, 1), "asset/sprites/r-typesheet42.gif", 3, surface(vector2D(33, 18), vector2D(33, 18)));
}

void EntityFactory::makePlayer(Engine::ClusterName clusterName, uint32_t entityId)
{
    Player(clusterName, {120, 200}, {10, 10}, {40, 40}, "asset/sprites/r-typesheet1.gif");
}

void EntityFactory::makeBullet0(Engine::ClusterName clusterName, uint32_t entityId)
{
    Bullet(clusterName, 0, vector2D(0, 0), vector2D(0, 0));
}

void EntityFactory::makeBullet1(Engine::ClusterName clusterName, uint32_t entityId)
{
    Bullet(clusterName, 1, vector2D(0, 0), vector2D(0, 0));
}

void EntityFactory::makeBullet2(Engine::ClusterName clusterName, uint32_t entityId)
{
    Bullet(clusterName, 2, vector2D(0, 0), vector2D(0, 0));
}

void EntityFactory::makeBullet3(Engine::ClusterName clusterName, uint32_t entityId)
{
    Bullet(clusterName, 3, vector2D(0, 0), vector2D(0, 0));
}

void EntityFactory::makeBullet4(Engine::ClusterName clusterName, uint32_t entityId)
{
    Bullet(clusterName, 4, vector2D(0, 0), vector2D(0, 0));
}

void EntityFactory::makeEquipment(Engine::ClusterName clusterName, uint32_t entityId)
{
    Equipment(clusterName, vector2D(0, 0));
}

void EntityFactory::makeExplosion(Engine::ClusterName clusterName, uint32_t entityId)
{
    Explosion(clusterName, vector2D(0, 0));
}