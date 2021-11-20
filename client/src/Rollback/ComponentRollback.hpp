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

    template <class ComponentType>
    static void ApplyComponent(Engine::Entity id, void *component, long);

  private:
    static const std::unordered_map<std::size_t, std::function<void(Engine::Entity, void *, long int)>>
        hashcodeComponents;
};

template <class ComponentType>
void ComponentRollback::ApplyComponent(Engine::Entity id, void *component, long)
{
    try {
        auto &oldComponent = GET_COMP_M.get<ComponentType>(id);

        std::memcpy((void *) &oldComponent, component, sizeof(ComponentType));
    } catch (Engine::NotFoundException const &) {
        // the component doesn't exist anymore. Ignore
    } catch (std::exception const &e) {
        std::cerr << "ComponentRollback::ApplyComponent Fail to apply changes" << std::endl;
    }
}
#endif // R_TYPE_SERVER_COMPONENTROLLBACK_HPP