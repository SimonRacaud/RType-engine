/*
** EPITECH PROJECT, 2021
** ComponentRollback.cpp
** File description:
** Apply component received from the network to the local game engine
*/

#include "ComponentRollback.hpp"

#include "Components/Health.hpp"
#include "Components/AnimationInfo.hpp"
#include "Component/Render.hpp"

/**
 * @brief Refresh rate of the physic system in milliseconds
 */
static const float PhysicSystemRefreshRate = 10;

const std::unordered_map<std::size_t, std::function<void(Engine::Entity, void *, long int)>> ComponentRollback::hashcodeComponents{
        {Engine::Position::type.hash_code(), ComponentRollback::RollbackPosition},
        {Engine::Velocity::type.hash_code(), ComponentRollback::ApplyComponent<Engine::Velocity>},
        {Engine::ScoreComponent::type.hash_code(), ComponentRollback::ApplyComponent<Engine::ScoreComponent>},
        {Engine::EquipmentComponent::type.hash_code(), ComponentRollback::ApplyComponent<Engine::EquipmentComponent>},
        {Component::Health::type.hash_code(), ComponentRollback::ApplyComponent<Component::Health>},
        {Component::AnimationInfo::type.hash_code(), ComponentRollback::ApplyAnimationInfo}
    };

void ComponentRollback::Apply(Tram::ComponentSync const &tram)
{
    const Engine::Entity entity = GET_ENTITY_M.getId(tram.networkId);

    if (hashcodeComponents.contains(tram.componentType)) {
        hashcodeComponents.at(tram.componentType)(entity, tram.component, tram.timestamp);
    } else {
        std::cerr << "ComponentRollback::Apply component not found." << std::endl;
    }
}

#include "AnimationManager/AnimationManager.hpp"


void ComponentRollback::ApplyAnimationInfo(Engine::Entity id, void *component, long)
{
    try {
        Component::AnimationInfo *info = reinterpret_cast<Component::AnimationInfo *>(component);
        auto &render = GET_COMP_M.get<Engine::Render>(id);
        auto &hitbox = GET_COMP_M.get<Engine::Hitbox>(id);

        if (render._src.empty() == false) {
            auto *enemyRender = reinterpret_cast<AnimationManager *>(render._src[0].get());

            enemyRender->setSrcPath(info->_path);
            enemyRender->setPosition(info->_animPos);
            enemyRender->setNbMember(info->_nbFrames);
            enemyRender->refresh();
        }
        // update hitbox size
        hitbox.x = (float)info->_animSize.x;
        hitbox.y = (float)info->_animSize.y;
    } catch (Engine::NotFoundException const &) {
        // the component doesn't exist anymore. Ignore
    } catch (std::exception const &e) {
        std::cerr << "ComponentRollback::ApplyComponent Fail to apply changes" << std::endl;
    }
}

void ComponentRollback::RollbackPosition(Engine::Entity id, void *component, long int timestamp)
{
    auto &oldComponent = GET_COMP_M.get<Engine::Position>(id);
    const auto &velocity = GET_COMP_M.get<Engine::Velocity>(id);
    const Engine::Position *newComponent = reinterpret_cast<Engine::Position *>(component);
    float deltaTime = (GET_NOW - timestamp);
    float numberMissingCycle = (deltaTime / PhysicSystemRefreshRate);

    oldComponent.x = newComponent->x + (velocity.x * numberMissingCycle);
    oldComponent.y = newComponent->y + (velocity.y * numberMissingCycle);
}
