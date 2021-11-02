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
#include "IEntityManager.hpp"
#include "FactoryShortcuts.hpp"
#include "EngineFactory.hpp"
#include "ComponentManager.hpp"

namespace Engine
{
    #define GET_COMP_M   EngineFactory::getInstance().getComponentManager()

    class EntityManager : public IEntityManager {
      public:
        friend class ComponentManager;

        explicit EntityManager();
        ~EntityManager() = default;

        Entity create(EntityDestructor destructor = nullptr, ClusterName cluster = ClusterName::GLOBAL,
            EntityName name = EntityName::EMPTY,
            bool setNetworkId = false);

        void remove(Entity entity);
        void remove(EntityName name);
        void remove(ClusterName cluster);

        bool exist(Entity entity);
        bool exist(EntityName name, ClusterName cluster = ClusterName::GLOBAL);

        Entity getId(EntityName name);
        std::size_t getClusterSize(ClusterName cluster);

        Entity getId(NetworkId id);
        void setNetworkId(Entity entity, NetworkId networkId);

      private:
        void _allocate(std::size_t size);
        std::vector<Signature> _getSignatureList();

        const Signature _getSignature(Entity entity);

        EntityRegister &_getEntityRegister();

      private:
        EntityRegister _entities;
    };
} // namespace Engine

#endif // ENTITYMANAGER_HPP