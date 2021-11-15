/*
** EPITECH PROJECT, 2021
** BulletServer
** File description:
** BulletServer.cpp
*/

#include "BulletServer.hpp"
#include "ServerCore/ServerCore.hpp"

BulletServer::BulletServer(const vector2D &pos, const vector2D &velocity, const vector2D &size)
{
    Engine::IEntityManager &entityManager = ServerCore::engine.getEntityManager();
    Engine::ComponentManager &componentManager = ServerCore::engine.getComponentManager();
    Engine::Entity entity = entityManager.create(nullptr, Engine::ClusterName::START, Engine::EntityName::TEST);

    componentManager.add<Engine::Position>(entity, pos.x, pos.y);
    componentManager.add<Engine::Velocity>(entity, velocity.x, velocity.y);
    componentManager.add<Engine::Hitbox>(entity, size.x, size.y, [](Engine::Entity a, Engine::Entity b) {
        ServerCore::engine.getEntityManager().remove(a);
        ServerCore::engine.getEntityManager().remove(b);
        // ADD EXPLOSION ANIMATION
    });
    // TODO ADD SyncSendComponent WHEN READY
}