/*
** EPITECH PROJECT , 2021
** IEntityManager
** File description:
** \file IEntityManager.hpp
** \author simon
** \brief
** \date 02/11/2021
*/

#ifndef IENTITYMANAGER_HPP
#define IENTITYMANAGER_HPP

#include "global.hpp"
#include "EntityRegister/EntityRegister.hpp"
#include <vector>
#include <stddef.h>

namespace Engine {
    class IEntityManager {
      public:
        virtual ~IEntityManager() = default;

        virtual Entity create(EntityDestructor destructor, ClusterName cluster,
            EntityName name, bool setNetworkId) = 0;

        virtual void remove(Entity entity) = 0;
        virtual void remove(EntityName name) = 0;
        virtual void remove(ClusterName cluster) = 0;

        virtual bool exist(Entity entity) = 0;
        virtual bool exist(EntityName name, ClusterName cluster) = 0;

        virtual Entity getId(EntityName name) = 0;
        virtual std::size_t getClusterSize(ClusterName cluster) = 0;

        virtual Entity getId(NetworkId id) = 0;
        virtual void setNetworkId(Entity entity, NetworkId networkId) = 0;

      private:
        virtual std::vector<Signature> _getSignatureList() = 0;
        virtual const Signature _getSignature(Entity entity) = 0;

        virtual EntityRegister &_getEntityRegister() = 0;
    };
}

#endif // IENTITYMANAGER_HPP
