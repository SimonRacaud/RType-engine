/*
** EPITECH PROJECT, 2021
** EntityFactory
** File description:
** EntityFactory.hpp
*/

#ifndef ENTITYFACTORY_HPP
#define ENTITYFACTORY_HPP

#include <functional>
#include <string>
#include "Components/EntityMask.hpp"
#include "CustomCluster.hpp"
#include "Item/vector2D.hpp"
#include "Network/Tram/CreateEntityRequest.hpp"
#include "utils/netVector2f.hpp"
#include <unordered_map>

using Network::netVector2f;
using Tram::CreateEntityRequest;

class EntityFactory {
  public:
    EntityFactory(Engine::ClusterName clusterName);
    ~EntityFactory() = default;

    void build(CreateEntityRequest const &request);

    void createPlayer(vector2D const &position, vector2D const &velocity, int playerNumber);
    void createBullet(vector2D const &position, vector2D const &velocity, Component::MASK owner, size_t charge);

  private:
    static void makePlayer(Engine::ClusterName clusterName, CreateEntityRequest const &request);
    static void makeEnemy(Engine::ClusterName clusterName, CreateEntityRequest const &request);
    static void makeBullet(Engine::ClusterName clusterName, CreateEntityRequest const &request);
    static void makeEquipment(Engine::ClusterName clusterName, CreateEntityRequest const &request);
    static void makeExplosion(Engine::ClusterName clusterName, CreateEntityRequest const &request);

  private:
    Engine::ClusterName _clusterName;
    const std::unordered_map<std::string, std::function<void(Engine::ClusterName, CreateEntityRequest const &)>>
        _factory = {
            {"Enemy", EntityFactory::makeEnemy},
            {"Player", EntityFactory::makePlayer}, // Format "^Player([0-4])$"
            {"Bullet", EntityFactory::makeBullet}, // Format "^Bullet[0-4]?(Enemy|Player)$"
            {"Equipment", EntityFactory::makeEquipment},
            {"Explosion", EntityFactory::makeExplosion},
    };
};

#endif