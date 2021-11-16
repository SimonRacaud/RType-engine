/*
** EPITECH PROJECT, 2021
** ComponentRollback.hpp
** File description:
** TODO: add description
*/
#ifndef R_TYPE_SERVER_COMPONENTROLLBACK_HPP
#define R_TYPE_SERVER_COMPONENTROLLBACK_HPP

#include <functional>
#include "EngineCore.hpp"
#include <unordered_map>

class ComponentRollback {
  public:
    static void Apply(Engine::Entity id, size_t componentTypeHash, void *component, long int timestamp);

    //    GET_COMP_M

  private:
    static void RollbackPosition(Engine::Entity id, void *component, long int timestamp);

  private:
    static const std::unordered_map<std::size_t, std::function<void(Engine::Entity, void *, long int)>>
        hashcodeComponents;
    // component position to be changed

    // componentManager :
    //  component velocity
    // temps
};

#endif // R_TYPE_SERVER_COMPONENTROLLBACK_HPP