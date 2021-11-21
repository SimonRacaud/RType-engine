/*
** EPITECH PROJECT, 2021
** ComponentRollback.cpp
** File description:
** Apply component received from the network to the local game engine
*/

#include "GameCore/GameCore.hpp"
#include "ComponentRollback.hpp"

#include "Components/Health.hpp"
#include "Components/AnimationInfo.hpp"
#include "Component/Render.hpp"
#include "AnimationManager/AnimationManager.hpp"

static void applyVelocity(Engine::Entity id, void *component, long)
{
    auto *shared = reinterpret_cast<Engine::Velocity *>(component);
    auto &local = GET_COMP_M.get<Engine::Velocity>(id);

    local.x = shared->x;
    local.y = shared->y;
}

static void applyScore(Engine::Entity id, void *component, long)
{
    auto *shared = reinterpret_cast<Engine::ScoreComponent *>(component);
    auto &local = GET_COMP_M.get<Engine::ScoreComponent>(id);

    local.value = shared->value;
}

static void applyEquipment(Engine::Entity id, void *component, long)
{
    auto *shared = reinterpret_cast<Engine::EquipmentComponent *>(component);
    auto &local = GET_COMP_M.get<Engine::EquipmentComponent>(id);

    local.counter = shared->counter;
}

static void applyHealth(Engine::Entity id, void *component, long)
{
    auto *shared = reinterpret_cast<Component::Health *>(component);
    auto &local = GET_COMP_M.get<Component::Health>(id);

    local._health = shared->_health;
}

const std::unordered_map<std::size_t, std::function<void(Engine::Entity, void *, long int)>> ComponentRollback::hashcodeComponents{
        {Engine::Position::type.hash_code(), ComponentRollback::RollbackPosition},
        {Engine::Velocity::type.hash_code(), applyVelocity},
        {Engine::ScoreComponent::type.hash_code(), applyScore},
        {Engine::EquipmentComponent::type.hash_code(), applyEquipment},
        {Component::Health::type.hash_code(), applyHealth},
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

void ComponentRollback::ApplyAnimationInfo(Engine::Entity id, void *component, long)
{
    try {
        Component::AnimationInfo *info = reinterpret_cast<Component::AnimationInfo *>(component);
        auto &render = GET_COMP_M.get<Engine::Render>(id);
        auto &hitbox = GET_COMP_M.get<Engine::Hitbox>(id);

        if (render._src.empty() == false) {
            auto *enemyRender = reinterpret_cast<AnimationManager *>(render._src[0].get());

            const surface surface(info->_animPos, info->_animSize);
            enemyRender->setFocus(surface);
            enemyRender->setSrcPath(info->_path);
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
    static vector2D winsize = GameCore::config->getVar<vector2D>("WINDOW_SIZE");
    auto &oldComponent = GET_COMP_M.get<Engine::Position>(id);
    const auto &velocity = GET_COMP_M.get<Engine::Velocity>(id);
    const Engine::Position *newComponent = reinterpret_cast<Engine::Position *>(component);
    float deltaTime = (GET_NOW - timestamp) / 1000;
    float x = newComponent->x + (velocity.x * deltaTime);
    float y = newComponent->y + (velocity.y * deltaTime);
    bool update = x < 0 || y < 0 || x > winsize.x || y > winsize.y;

    if (!update) {
        oldComponent.x = x;
        oldComponent.y = y;
    }
}
