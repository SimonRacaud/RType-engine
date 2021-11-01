/*
** EPITECH PROJECT, 2021
** GameEngine
** File description:
** 01/06/2021 EntityManager.cpp.c
*/

#include "EntityManager.hpp"

using namespace Engine;

EntityManager::EntityManager()
{
    this->_allocate(ALLOCATE_NB_ENTITY);
}

Entity EntityManager::create(EntityDestructor destructor, ClusterName cluster,
    EntityName entity, bool setNetworkId)
{
    // TODO
    return 0;
}

void EntityManager::setAsPublic(Entity privateId, Entity publicId)
{
    // TODO
}

void EntityManager::remove(Entity entity)
{
    // TODO
    // Hey Entity Register, remove "entity" from your register
    //    _entities.remove(entity);
    // Hey systems! Remove "entity" from your managed entity lists
    //    this->_systemManager.onEntityRemoved(entity);
    // Hey BaseComponent Registers! Remove the instances of the Components of
    // "entity".
    //    for (auto &componentRegister : _componentRegisters) {
    //        if (componentRegister != nullptr) {
    //            componentRegister->tryRemove(entity);
    //        }
    //    }
}

void EntityManager::remove(EntityName name)
{
    // TODO
}

void EntityManager::remove(ClusterName cluster)
{
    // TODO
}

bool EntityManager::exist(Entity entity)
{
    return _entities.exist(entity);
}

bool EntityManager::exist(ClusterName cluster, EntityName name)
{
    // TODO
    return false;
}

Entity EntityManager::getId(NetworkId id)
{
    return _entities.getId(id);
}

void EntityManager::setNetworkId(Entity entity, NetworkId networkId)
{
    _entities.setNetworkId(entity, networkId);
}

void EntityManager::_allocate(std::size_t size)
{
    _entities.allocate(size);
}

std::vector<Signature> EntityManager::_getSignatureList()
{
    // TODO
    //    std::vector<Signature> &publicSign =
    //    this->_public.getSignatureList(); std::vector<Signature> &privateSign
    //    = this->_private.getSignatureList();
    std::vector<Signature> result;

    //    result.insert(result.end(), publicSign.begin(), publicSign.end());
    //    result.insert(result.end(), privateSign.begin(), privateSign.end());
    return result;
}

const Signature EntityManager::_getSignature(Entity entity)
{
    // TODO
    return Signature();
}