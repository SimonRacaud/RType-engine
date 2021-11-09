/*
** EPITECH PROJECT, 2021
** GameEngine
** File description:
** 27/05/2021 EntityRegister.hpp.h
*/

#ifndef ENTITYREGISTER_HPP
#define ENTITYREGISTER_HPP

#include <iostream>
#include <cstddef>
#include <vector>
#include <numeric>
#include "ClusterName.hpp"
#include "EntityBlock.hpp"
#include "EntityName.hpp"
#include "Exception/InvalidParameterException.hpp"
#include "Exception/NotFoundException.hpp"
#include "NetworkIdRegister/NetworkIdRegister.hpp"
#include "env.hpp"
#include "global.hpp"

namespace Engine
{
    using std::vector;

    class EntityRegister {
      public:
        EntityRegister() = default;
        virtual ~EntityRegister() = default;

        /**
         * @brief Perf optimisation
         * @param size
         */
        void allocate(std::size_t size);
        /**
         * @brief List that register what components the entities have.
         * @return std::vector<Signature>
         */
        std::vector<Signature> &getSignatureList();
        /**
         * @brief List that register what components the entity has.
         * @throws NotFoundException : entity not found
         * @param entity
         * @return const Signature
         */
        [[nodiscard]] const Signature &getSignature(Entity entity) const;
        /**
         * @brief Create an entity
         * @param cluster : cluster of the entity
         * @param name  : name of the entity (optional)
         * @param destructor : destructor callback
         * @param setNetworkId : attribute an unique network id ?
         * @return Entity
         */
        Entity create(ClusterName cluster, EntityName name,
            EntityDestructor destructor, bool setNetworkId = false);
        /**
         * @brief remove an entity
         * @throws NotFoundException : entity not found
         * @param entity
         */
        void remove(Entity entity);
        /**
         * @throws NotFoundException : entity name not found
         * @param name
         * @return
         */
        Entity remove(EntityName name);

        /**
         * @brief Clear the entities of a cluster
         * @throws NotFoundException
         * @param cluster
         * @return
         */
        vector<Entity> remove(ClusterName cluster);
        /**
         * @brief Do the entity exist ?
         * @param entity
         * @return
         */
        [[nodiscard]] bool exist(Entity entity) const;
        /**
         * @brief Do the entity name of the cluster exist ?
         * @param name
         * @param cluster
         * @return
         */
        [[nodiscard]] bool exist(EntityName name, ClusterName cluster = ClusterName::GLOBAL) const;
        /**
         * @brief Get the entity id linked the entity name
         * @throws NotFoundException
         * @param name
         * @return
         */
        [[nodiscard]] Entity getId(EntityName name) const;
        /**
         * @brief Get the entity id linked to that network id
         * @throws NotFoundException
         * @throws FatalErrorException : no network id
         * @param networkId
         * @return
         */
        [[nodiscard]] Entity getId(NetworkId networkId) const;
        /**
         * @brief Get the number of entity in a cluster
         * @param cluster
         * @return
         */
        [[nodiscard]] size_t getClusterSize(ClusterName cluster) const;
        /**
         * @brief Set a network id to an entity
         * @throws InvalidParameterException : entity not found
         * @param entity
         * @param id
         */
        void setNetworkId(Entity entity, NetworkId id);

        /**
         * @brief Get a list of all entities (used to clear all entities)
         */
        vector<Entity> getEntityList() const;

      private:
        [[nodiscard]] vector<Entity> getClusterEntityList(ClusterName cluster) const;

      private:
        std::vector<Signature> _signatures;
        std::vector<EntityBlock> _bookedEntities;
        std::vector<Entity> _freeEntities;
        NetworkIdRegister _networkIdRegister;
    };
} // namespace Engine

#endif // ENTITYREGISTER_HPP