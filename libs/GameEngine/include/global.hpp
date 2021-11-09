/**
 * EPITECH PROJECT, 2021
 * GameEngine
 * \brief Custom type definition
 * \author simon.racaud
 */

#ifndef GLOBAL_HPP
#define GLOBAL_HPP

#include <bitset>
#include <memory>
#include <cstdint>
#include <functional>
#include <limits>
#include <typeindex>
#include <typeinfo>
#include <chrono>

#include "ClusterName.hpp"
#include "EntityName.hpp"
#include "env.hpp"
#include "Event/IEvent.hpp"

namespace Engine
{
    using Entity = uint32_t;

    using Index = uint32_t;

    using TypeIdx = std::type_index;
    #define GET_TYPE_IDX(type) std::type_index(typeid(type))

    using NetworkId = uint32_t;

    using EventCallbackSignature =
        std::function<void(const Engine::Event::IEvent *)>;

    using EntityDestructor =
        std::function<void(Entity, EntityName, ClusterName)>;
    using std::unique_ptr;

    template <class ComponentType>
    using ComponentBrowseFunction = std::function<void(unique_ptr<ComponentType> &)>;

    using Time = std::chrono::milliseconds;
    using DurationCast = std::chrono::duration<Time>;
    using Clock = std::chrono::steady_clock;
    using TimePoint = std::chrono::time_point<Clock>;

    static constexpr Entity MaxEntity = std::numeric_limits<Entity>::max();
    static constexpr Index InvalidIndex = std::numeric_limits<Index>::max();

    typedef std::bitset<MAX_COMPONENT_TYPE> Signature;

    #ifdef ENABLE_DEBUG
        #define SHOW_DEBUG(message) (std::cerr << message << std::endl)
        #define SHOW_DEBUG_COMPONENT(message) if (DEBUG_COMPONENT) SHOW_DEBUG(message)
    #else
        #define SHOW_DEBUG(message)
    #endif
    #define TYPE_STR(type) std::to_string(type.hash_code())
} // namespace Engine

#endif // GLOBAL_HPP
