/*
** EPITECH PROJECT, 2021
** EntityFactory
** File description:
** EntityFactory.cpp
*/

#include <stdexcept>
#include <regex>
#include "EntityFactory.hpp"

#include "Entities/Enemy/Enemy.hpp"
#include "Entities/Bullet/Bullet.hpp"
#include "Entities/Player/Player.hpp"
#include "Entities/Explosion/Explosion.hpp"
#include "Entities/Equipment/Equipment.hpp"

EntityFactory::EntityFactory(Engine::ClusterName clusterName) : _clusterName(clusterName)
{
}

void EntityFactory::build(const CreateEntityRequest &request)
{
    try {
        for (auto [type, callback] : _factory) {
            if (std::string(request.entityType).starts_with(type)) {
                callback(_clusterName, request);
            }
        }
    } catch (std::exception const &e) {
        std::cerr << "[Exception] EntityFactory " << e.what() << std::endl;
        throw std::invalid_argument("EntityFactory::build an exception occurred");
    }
}

void EntityFactory::create(const std::string &entityType, const netVector2f &position,
    const netVector2f &velocity)
{
    // TODO
}

void EntityFactory::makePlayer(Engine::ClusterName clusterName, const CreateEntityRequest &request)
{
    std::string type = request.entityType;
    std::regex regex("^Player([0-4])$");
    std::smatch match;

    if (std::regex_search(type, match, regex)) {
        int playerId = std::stoi(match[0]);
        vector2D position(request.position.x, request.position.y);
        vector2D velocity(request.velocity.x, request.velocity.y);

        Player player(clusterName, playerId, position, velocity);
        player.setNetworkId(request.id);
    } else {
        throw std::invalid_argument("EntityFactory::makePlayer regex fail");
    }
}

void EntityFactory::makeEnemy(Engine::ClusterName clusterName, CreateEntityRequest const& request)
{
    const vector2D position(request.position.x, request.position.y);
    const vector2D velocity(request.velocity.x, request.velocity.y);
    const vector2f scale(1, 1);
    const size_t nbStep = 3;
    const surface surface(vector2D(33, 18), vector2D(33, 18));

    Enemy(clusterName, position, velocity, scale, "asset/sprites/r-typesheet42.gif",
        nbStep, surface).setNetworkId(request.id);
}

void EntityFactory::makeBullet(Engine::ClusterName clusterName, CreateEntityRequest const& request)
{
    const std::string type = request.entityType;
    std::regex regex("^Bullet([0-4])?(Enemy|Player)$");
    std::smatch match;

    if (std::regex_search(type, match, regex)) {
        size_t bulletType = (size_t)std::stoi(match[0]);
        const std::string owner = match[1];
        const vector2D position(request.position.x, request.position.y);
        const vector2D velocity(request.velocity.x, request.velocity.y);

        Bullet(clusterName, bulletType, position, velocity, owner).setNetworkId(request.id);
    } else {
        throw std::invalid_argument("EntityFactory::makeBullet regex fail");
    }
}

void EntityFactory::makeEquipment(Engine::ClusterName clusterName, CreateEntityRequest const& request)
{
    const vector2D position(request.position.x, request.position.y);

    Equipment(clusterName, position).setNetworkId(request.id);
}

void EntityFactory::makeExplosion(Engine::ClusterName clusterName, CreateEntityRequest const& request)
{
    const vector2D position(request.position.x, request.position.y);

    Explosion(clusterName, position).setNetworkId(request.id);
}