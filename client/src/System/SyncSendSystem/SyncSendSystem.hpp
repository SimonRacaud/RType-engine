/*
** EPITECH PROJECT , 2021
** SyncSendSystem
** File description:
** SyncSendSystem.hpp
*/

#ifndef SYNCSENDSYSTEM_HPP
#define SYNCSENDSYSTEM_HPP

#include "EngineCore.hpp"

namespace System
{
    class SyncSendSystem : public Engine::AbstractSystem<SyncSendSystem> {
      public:
        SyncSendSystem();

        void run(const std::vector<Engine::Entity> &entities) override;

        void onManagedEntityAdded(Engine::Entity) override;

      private:
        void syncEntity(Engine::Entity entity);

      private:
        bool _isMaster{false};
    };
} // namespace System

#endif