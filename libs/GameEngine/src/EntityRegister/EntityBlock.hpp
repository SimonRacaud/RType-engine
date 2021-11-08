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
    /**
     * @brief Stock the information about one entity
     */
    class EntityBlock {
      private:
        Entity _entity{0};
        EntityName _name{0};
        ClusterName _cluster{0};
        EntityDestructor _destructor{nullptr};
        NetworkId _networkId{NO_NET_ID};

      public:
        EntityBlock() = default;
        EntityBlock(Entity entity, ClusterName cluster, EntityName name,
            EntityDestructor destructor);
        EntityBlock(EntityBlock const& block);
        virtual ~EntityBlock() = default;

        bool operator==(Entity entity);
        bool operator==(EntityName name);
        bool operator==(ClusterName cluster);
        EntityBlock &operator=(EntityBlock const& block);

        Entity getEntity() const;
        void setEntity(Entity entity);
        EntityName getName() const;
        ClusterName getCluster() const;
        void destroy();
        void setNetworkId(NetworkId id);
        NetworkId getNetworkId() const;

      public:
        bool removed{true};
    };
} // namespace Engine

#endif // ENTITYBLOCK_HPP
