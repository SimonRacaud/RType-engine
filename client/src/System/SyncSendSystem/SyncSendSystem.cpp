/*
** EPITECH PROJECT , 2021
** SyncSendSystem
** File description:
** SyncSendSystem.cpp
*/

#include "SyncSendSystem.hpp"

#include <iostream>
#include <stdexcept>

#include "Component/SyncSend.hpp"
#include "Components/AnimationInfo.hpp"
#include "Components/Health.hpp"

#include "GameCore/GameCore.hpp"

using namespace System;
using Component::MASK;

static const Engine::Time freq = static_cast<Engine::Time>(100);

System::SyncSendSystem::SyncSendSystem() : Engine::AbstractSystem<SyncSendSystem>(freq)
{
    this->setRequirements<Component::SyncSend, Component::EntityMask>();
}

void System::SyncSendSystem::run(const std::vector<Engine::Entity> &entities)
{
    try {
        for (Engine::Entity entity : entities) {
            auto &mask = GameCore::engine.getComponentManager().get<Component::EntityMask>(entity);
            bool needSync = mask._currentMask == MASK::PLAYER || (_isMaster
                              && (mask._currentMask == MASK::BULLET_PLAYER || mask._currentMask == MASK::BULLET_ENEMY
                                  || mask._currentMask == MASK::EQUIPMENT));
            if (!needSync) {
                continue; // don't sync that entity.
            }
            this->syncEntity(entity);
        }
    } catch (std::exception const& e) {
        std::cerr << "SyncSendSystem::run Exception : " << e.what() << std::endl;
    }
}

template <class ComponentType>
static void syncComponent(Engine::Entity entity, Engine::NetworkId networkId)
{
    auto &component = GameCore::engine.getComponentManager().get<ComponentType>(entity);

    GameCore::networkCore.syncComponent(networkId, ComponentType::type,
        sizeof(ComponentType), static_cast<void *>(&component));
}

void SyncSendSystem::syncEntity(Engine::Entity entity)
{
    auto &syncSend = GameCore::engine.getComponentManager().get<Component::SyncSend>(entity);
    Engine::NetworkId networkId = GameCore::engine.getEntityManager().getNetworkId(entity);

    if (syncSend._syncFlag & Component::SyncComponentType::POSITION) {
        syncComponent<Engine::Position>(entity, networkId);
    }
    if (syncSend._syncFlag & Component::SyncComponentType::VELOCITY) {
        syncComponent<Engine::Velocity>(entity, networkId);
    }
    if (syncSend._syncFlag & Component::SyncComponentType::SCORE) {
        syncComponent<Engine::ScoreComponent>(entity, networkId);
    }
    if (syncSend._syncFlag & Component::SyncComponentType::EQUIPMENT_COMP) {
        syncComponent<Engine::EquipmentComponent>(entity, networkId);
    }
    if (syncSend._syncFlag & Component::SyncComponentType::ANIMATION_INFO) {
        syncComponent<Component::AnimationInfo>(entity, networkId);
    }
    if (syncSend._syncFlag & Component::SyncComponentType::HEALTH) {
        syncComponent<Component::Health>(entity, networkId);
    }
}

void SyncSendSystem::onManagedEntityAdded(Engine::Entity)
{
    // Optimisation des performances (limitation des appels à cette méthodes)
    this->_isMaster = GameCore::networkCore.isMaster();
}