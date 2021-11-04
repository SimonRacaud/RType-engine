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
#include "Engine/EngineFactory.hpp"
#include "ComponentManager/ComponentManager.hpp"

namespace Engine
{
    #define GET_COMP_M   EngineFactory::getInstance().getComponentManager()

    /**
     * @brief Management of the entities
     */
    class EntityManager : public IEntityManager {
      public:
        friend class ComponentManager;

        explicit EntityManager();
        ~EntityManager() = default;

        /**
         * @brief Create a new entity
         * @param destructor : callback
         * @param cluster : cluster name
         * @param name : entity name (optional)
         * @param setNetworkId : unique id for the network (optional)
         * @return
         */
        Entity create(EntityDestructor destructor = nullptr, ClusterName cluster = ClusterName::GLOBAL,
            EntityName name = EntityName::EMPTY,
            bool setNetworkId = false);

        /**
         * @brief remove the entity
         * @throws NotFoundException
         * @param entity
         */
        void remove(Entity entity);
        /**
         * @brief remove the entity
         * @throws NotFoundException
         * @param entity
         */
        void remove(EntityName name);
        /**
         * @brief remove the entity
         * @throws NotFoundException
         * @param entity
         */
        void remove(ClusterName cluster);

        /**
         * @brief Do the entity exist?
         * @param entity
         * @return
         */
        bool exist(Entity entity);
        /**
         * @brief Do the named entity in that cluster exist?
         * @param name
         * @param cluster
         * @return
         */
        bool exist(EntityName name, ClusterName cluster = ClusterName::GLOBAL);

        /**
         * @brief Get the entity id linked to that name
         * @throws NotFoundException
         * @param name
         * @return
         */
        Entity getId(EntityName name);
        /**
         * @brief Get the number of entity in a cluster
         * @param cluster
         * @return
         */
        std::size_t getClusterSize(ClusterName cluster);
        /**
         * @brief Get the entity id linked to that network id
         * @throws NotFoundException
         * @throws FatalErrorException
         * @param id
         * @return
         */
        Entity getId(NetworkId id);
        /**
         * @brief Set a network id to an entity
         * @throws InvalidParameterException : entity not found
         * @throws FatalErrorException : network id already reserved
         * @param entity
         * @param networkId
         */
        void setNetworkId(Entity entity, NetworkId networkId);

      private:
        void _allocate(std::size_t size);

        std::vector<Signature> _getSignatureList();
        /**
         * @throws NotFoundException
         */
        const Signature _getSignature(Entity entity);

        EntityRegister &_getEntityRegister();

      private:
        EntityRegister _entities;
    };
} // namespace Engine

#endif // ENTITYMANAGER_HPP