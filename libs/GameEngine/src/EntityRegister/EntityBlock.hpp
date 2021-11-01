/*
** EPITECH PROJECT , 2021
** EntityBlock
** File description:
** \file EntityBlock.hpp
** \author simon
** \brief
** \date 01/11/2021
*/

#ifndef ENTITYBLOCK_HPP
#define ENTITYBLOCK_HPP

#include "ClusterName.hpp"
#include "EntityName.hpp"
#include "global.hpp"

namespace Engine
{
    class EntityBlock {
      private:
        Entity _entity;
        EntityName _name;
        ClusterName _cluster;
        EntityDestructor _destructor;
        NetworkId _networkId;

      public:
        EntityBlock(Entity entity, ClusterName cluster, EntityName name,
            EntityDestructor destructor);
        virtual ~EntityBlock() = default;

        bool operator==(Entity entity);
        bool operator==(EntityName name);
        bool operator==(ClusterName cluster);
        Entity getEntity() const;
        void setEntity(Entity entity);
        EntityName getName() const;
        ClusterName getCluster() const;
        void destroy();
        void setNetworkId(NetworkId id);
        NetworkId getNetworkId() const;
    };
} // namespace Engine

#endif // ENTITYBLOCK_HPP
