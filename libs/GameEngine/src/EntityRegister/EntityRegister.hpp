/*
** EPITECH PROJECT, 2021
** GameEngine
** File description:
** 27/05/2021 EntityRegister.hpp.h
*/

#ifndef ENTITYREGISTER_HPP
#define ENTITYREGISTER_HPP

#include <cstddef>
#include <vector>
#include <numeric>
#include "ClusterName.hpp"
#include "EntityBlock.hpp"
#include "EntityName.hpp"
#include "Exception/NotFoundException.hpp"
#include "NetworkIdRegister/NetworkIdRegister.hpp"
#include "env.hpp"
#include "global.hpp"

namespace Engine
{
    class EntityRegister {
      public:
        EntityRegister() = default;
        virtual ~EntityRegister() = default;

        void allocate(std::size_t size);
        std::vector<Signature> &getSignatureList();
        const Signature &getSignature(Entity entity) const;
        Entity create(ClusterName cluster, EntityName name,
            EntityDestructor destructor, bool setNetworkId = false);
        void remove(Entity entity);
        void remove(EntityName name);
        void remove(ClusterName cluster);
        bool exist(Entity entity) const;
        bool exist(EntityName name, ClusterName cluster = ClusterName::GLOBAL) const;
        bool exist(ClusterName cluster) const;
        Entity getId(EntityName name) const;
        Entity getId(NetworkId networkId) const;
        size_t getClusterSize(ClusterName cluster) const;
        void setNetworkId(Entity entity, NetworkId id);

      private:
        std::vector<Signature> _signatures;
        std::vector<EntityBlock> _bookedEntities;
        std::vector<Entity> _freeEntities;
        NetworkIdRegister _networkIdRegister;
    };
} // namespace Engine

#endif // ENTITYREGISTER_HPP