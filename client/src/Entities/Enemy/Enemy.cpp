/*
** EPITECH PROJECT, 2021
** Enemy
** File description:
** Enemy.cpp
*/

#include "Enemy.hpp"
#include "Component/Render.hpp"
#include "Component/EntityMask.hpp"
#include "AnimationManager/AnimationManager.hpp"

Enemy::Enemy(Engine::ClusterName clusterName, const vector2D &pos, const vector2D &velocity, const vector2f &scale, const std::string &path, size_t nbStep, const surface &focus)
{
    Engine::IEntityManager &entityManager = GameCore::engine.getEntityManager();
    Engine::ComponentManager &componentManager = GameCore::engine.getComponentManager();
    Engine::Entity entity = entityManager.create(nullptr, clusterName, Engine::EntityName::EMPTY);
    std::shared_ptr<AnimationManager> enemyRender = std::make_shared<AnimationManager>();

    enemyRender->setFocus(focus);
    enemyRender->setSrcPath(path);
    enemyRender->setPosition(pos);
    enemyRender->setNbMember(nbStep);
    enemyRender->setScale(scale);

    componentManager.add<Engine::Position>(entity, pos.x, pos.y);
    componentManager.add<Engine::Velocity>(entity, velocity.x, velocity.y);
    componentManager.add<Engine::Hitbox>(entity, focus.size.x, focus.size.y, [](Engine::Entity, Engine::Entity) {
        // TODO ADD CALLBACK
    });
    componentManager.add<Engine::Render>(entity, enemyRender);
    componentManager.add<Component::EntityMask>(entity, Component::MASK::ENEMY);
    _entity = entity;
}

void Enemy::setNetworkId(uint32_t entityId)
{
    GameCore::engine.getEntityManager().setNetworkId(_entity, entityId);
}