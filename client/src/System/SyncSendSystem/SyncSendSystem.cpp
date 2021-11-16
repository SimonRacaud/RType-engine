/*
** EPITECH PROJECT , 2021
** SyncSendSystem
** File description:
** SyncSendSystem.cpp
*/

#include "Component/SyncSend.hpp"
#include "SyncSendSystem.hpp"

System::SyncSendSystem::SyncSendSystem() : Engine::AbstractSystem<SyncSendSystem>()
{
    this->setRequirements<Component::SyncSend>();
}

void System::SyncSendSystem::run(const std::vector<Engine::Entity> &entities)
{
    for (auto &entity : entities) {
        auto [SyncSend, Mask] = Engine::EngineFactory::getInstance().getComponentManager().getList<Component::SyncSend, Component::EntityMask>(entity);
        if (SyncSend._type == Mask._currentMask) {
            if (SyncSend._syncFlag & Component::toSync::POSITION) {
                auto position = Engine::EngineFactory::getInstance().getComponentManager().get<Engine::Position>(entity);
                // TODO
            }
            if (SyncSend._syncFlag & Component::toSync::VELOCITY) {
                auto velocity = Engine::EngineFactory::getInstance().getComponentManager().get<Engine::Velocity>(entity);
                // TODO
            }
            if (SyncSend._syncFlag & Component::toSync::SCORE) {
                auto score = Engine::EngineFactory::getInstance().getComponentManager().get<Engine::ScoreComponent>(entity);
                // TODO
            }
        }
    }
}