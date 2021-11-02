/*
** EPITECH PROJECT, 2021
** GameEngine
** File description:
** 27/05/2021 EntityManager.hpp.h
*/

#ifndef ENTITYMANAGER_HPP
#define ENTITYMANAGER_HPP

#include <vector>
#include "EntityRegister/EntityRegister.hpp"
#include "global.hpp"
#include "ClusterName.hpp"
#include "EntityName.hpp"

namespace Engine
{
    class EntityManager {
        friend class ComponentManager;

      public:
        friend class ComponentManager;

        explicit EntityManager();
        ~EntityManager() = default;

        Entity create(EntityDestructor destructor = nullptr, ClusterName cluster = ClusterName::GLOBAL,
            EntityName entity = EntityName::EMPTY,
            bool setNetworkId = false);

        void setAsPublic(Entity privateId, Entity publicId);

        void remove(Entity entity);
        void remove(EntityName name);
        void remove(ClusterName cluster);

        bool exist(Entity entity);
        bool exist(ClusterName cluster = ClusterName::GLOBAL, EntityName name = EntityName::EMPTY);

        template <typename ComponentType>
        bool hasComponent(Entity entity);
        template <typename... ComponentTypeList>
        bool hasComponents(Entity entity);

        Entity getId(EntityName name);
        std::size_t getClusterSize(ClusterName cluster);

        Entity getId(NetworkId id);
        void setNetworkId(Entity entity, NetworkId networkId);

      private:
        void _allocate(std::size_t size);
        std::vector<Signature> _getSignatureList();
        const Signature _getSignature(Entity entity);

      private:
        EntityRegister _entities;
    };
} // namespace Engine

namespace Engine
{
    template <typename ComponentType>
    bool EntityManager::hasComponent(Entity entity)
    {
        // TODO
        //componentManager->checkComponentType<ComponentType>();
//        return _private.getSignature(entity)[ComponentType::type];
//        return _public.getSignature(entity)[ComponentType::type];
        return false;
    }

    template <typename... ComponentTypeList>
    bool EntityManager::hasComponents(Entity entity)
    {
        // TODO
        //(componentManager->checkComponentTypes<Ts>(), ...);
//        auto requirements = Signature();
//        (requirements.set(Ts::type), ...);
//        return (requirements & _entities.getSignature(entity)) == requirements;
        return false;
    }
} // namespace Engine

#endif // ENTITYMANAGER_HPP