/*
** EPITECH PROJECT, 2021
** Enemy
** File description:
** Enemy.cpp
*/

#include "Enemy.hpp"
#include "Component/Render.hpp"
#include "Components/EntityMask.hpp"
#include "Components/Health.hpp"
#include "AnimationManager/AnimationManager.hpp"
#include "Component/Damage.hpp"
#include "Event/EntityRemove/EntityRemoveEvent.hpp"

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
    componentManager.add<Component::Health>(entity, 1);
    componentManager.add<Engine::Hitbox>(entity, focus.size.x, focus.size.y, [](Engine::Entity a, Engine::Entity b) {
        Component::EntityMask otherMask = GET_COMP_M.get<Component::EntityMask>(b);
        auto &health = GET_COMP_M.get<Component::Health>(a);

        if (otherMask._currentMask == Component::MASK::BULLET_PLAYER) {
            auto dmg = GET_COMP_M.get<Component::Damage>(b);

            health._health -= dmg._damage;
            if (health._health <= 0) {
                GET_EVENT_REG.registerEvent<EntityRemoveEvent>(a);
            }
            try {
                /// Increase player score
                Engine::Entity player = GET_ENTITY_M.getId(Engine::EntityName::LOCAL_PLAYER);
                auto &score = GET_COMP_M.get<Engine::ScoreComponent>(player);
                score.value += (size_t) GameCore::config->getVar<int>("SCORE_INC");
            } catch (std::exception const &) {}
        }
    });
    componentManager.add<Engine::Render>(entity, enemyRender);
    componentManager.add<Component::EntityMask>(entity, Component::MASK::ENEMY);
    _entity = entity;
}

void Enemy::setNetworkId(uint32_t networkId)
{
    GameCore::engine.getEntityManager().forceApplyId(_entity, networkId);
}