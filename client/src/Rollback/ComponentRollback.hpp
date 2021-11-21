/*
** EPITECH PROJECT, 2021
** ComponentRollback.hpp
** File description:
** Apply component received from the network to the local game engine
*/

#ifndef R_TYPE_SERVER_COMPONENTROLLBACK_HPP
#define R_TYPE_SERVER_COMPONENTROLLBACK_HPP

#include <functional>
#include "EngineCore.hpp"
#include <unordered_map>
#include "Tram/ComponentSync.hpp"

class ComponentRollback {
  public:
    static void Apply(Tram::ComponentSync const &tram);

  private:
    static void RollbackPosition(Engine::Entity id, void *component, long int timestamp);

    static void ApplyAnimationInfo(Engine::Entity id, void *component, long int timestamp);

  private:
    static const std::unordered_map<std::size_t, std::function<void(Engine::Entity, void *, long int)>>
        hashcodeComponents;
};

#endif // R_TYPE_SERVER_COMPONENTROLLBACK_HPP