/*
** EPITECH PROJECT, 2021
** EntityFactory
** File description:
** EntityFactory.hpp
*/

#ifndef ENTITYFACTORY_HPP
#define ENTITYFACTORY_HPP

#include <string>
#include <functional>
#include <unordered_map>
#include "CustomCluster.hpp"

class EntityFactory
{
    public:
        EntityFactory(Engine::ClusterName clusterName);
        ~EntityFactory() = default;

        void build(const std::string &, uint32_t entityId);

    private:
        static void makeEnemy(Engine::ClusterName clusterName, uint32_t entityId);
        static void makePlayer(Engine::ClusterName clusterName, uint32_t entityId);
        static void makeBullet0(Engine::ClusterName clusterName, uint32_t entityId);
        static void makeBullet1(Engine::ClusterName clusterName, uint32_t entityId);
        static void makeBullet2(Engine::ClusterName clusterName, uint32_t entityId);
        static void makeBullet3(Engine::ClusterName clusterName, uint32_t entityId);
        static void makeBullet4(Engine::ClusterName clusterName, uint32_t entityId);
        static void makeEquipment(Engine::ClusterName clusterName, uint32_t entityId);
        static void makeExplosion(Engine::ClusterName clusterName, uint32_t entityId);

    private:
        // TODO UPDATE THE STRING WITH SIMON
        Engine::ClusterName _clusterName;
        const std::unordered_map<std::string, std::function<void (Engine::ClusterName clusterName, uint32_t entityId)>> _factory = {
            {"Enemy", EntityFactory::makeEnemy},
            {"Player", EntityFactory::makePlayer},
            {"Bullet0", EntityFactory::makeBullet0},
            {"Bullet1", EntityFactory::makeBullet1},
            {"Bullet2", EntityFactory::makeBullet2},
            {"Bullet3", EntityFactory::makeBullet3},
            {"Bullet4", EntityFactory::makeBullet4},
            {"Equipment", EntityFactory::makeEquipment},
            {"Explosion", EntityFactory::makeExplosion},
        };
};

#endif