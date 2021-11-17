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
#include "Tram/CreateEntityRequest.hpp"
#include "utils/netVector2f.hpp"

using Network::netVector2f;
using Tram::CreateEntityRequest;

class EntityFactory
{
    public:
        EntityFactory(Engine::ClusterName clusterName);
        ~EntityFactory() = default;

        void build(CreateEntityRequest const& request);

        void create(const std::string &entityType, netVector2f const& position,
            netVector2f const& velocity);

    private:
        static void makePlayer(Engine::ClusterName clusterName, CreateEntityRequest const& request);
        static void makeEnemy(Engine::ClusterName clusterName, CreateEntityRequest const& request);
        static void makeBullet(Engine::ClusterName clusterName, CreateEntityRequest const& request);
        static void makeEquipment(Engine::ClusterName clusterName, CreateEntityRequest const& request);
        static void makeExplosion(Engine::ClusterName clusterName, CreateEntityRequest const& request);

    private:
        Engine::ClusterName _clusterName;
        const std::unordered_map<std::string, std::function<void (Engine::ClusterName, CreateEntityRequest const&)>> _factory = {
            {"Enemy", EntityFactory::makeEnemy},
            {"Player", EntityFactory::makePlayer}, // Format "^Player([0-4])$"
            {"Bullet", EntityFactory::makeBullet}, // Format "^Bullet[0-4]?(Enemy|Player)$"
            {"Equipment", EntityFactory::makeEquipment},
            {"Explosion", EntityFactory::makeExplosion},
        };
};

#endif