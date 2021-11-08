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

EntityManager::~EntityManager() noexcept
{
    const std::vector<Entity> &list = this->_entities.getEntityList();

    for (Entity entity : list) {
        this->remove(entity);
    }
    SHOW_DEBUG("Entity: " + std::to_string(list.size()) + " entities removed.");
}

Entity EntityManager::create(EntityDestructor destructor, ClusterName cluster,
    EntityName name, bool setNetworkId)
{
    return _entities.create(cluster, name, destructor, setNetworkId);
}

void EntityManager::remove(Entity entity)
{
    // Hey Entity Register, remove [entity] from your register
    _entities.remove(entity);
     // Hey systems! Remove [entity] from your managed entity lists
    GET_SYS_M.onEntityRemoved(entity);
     // Hey BaseComponent Registers! Remove the instances of the Components of [entity].
    for (auto &componentRegister : GET_COMP_M._componentRegisters) {
        if (componentRegister != nullptr) {
            componentRegister->remove(entity);
        }
    }
}

void EntityManager::remove(EntityName name)
{
    // Hey Entity Register, remove [entity] from your register
    Entity entity = _entities.remove(name);
    // Hey systems! Remove [entity] from your managed entity lists
    GET_SYS_M.onEntityRemoved(entity);
    // Hey BaseComponent Registers! Remove the instances of the Components of [entity].
    for (auto &componentRegister : GET_COMP_M._componentRegisters) {
        if (componentRegister != nullptr) {
            componentRegister->remove(entity);
        }
    }
}

void EntityManager::remove(ClusterName cluster)
{
    // Hey Entity Register, remove [entity] from your register
    vector<Entity> entityList = _entities.remove(cluster);
    for (Entity entity : entityList) {
        // Hey systems! Remove [entity] from your managed entity lists
        GET_SYS_M.onEntityRemoved(entity);
        // Hey BaseComponent Registers! Remove the instances of the Components of [entity].
        for (auto &componentRegister : GET_COMP_M._componentRegisters) {
            if (componentRegister != nullptr) {
                componentRegister->remove(entity);
            }
        }
    }
}

bool EntityManager::exist(Entity entity)
{
    return _entities.exist(entity);
}

bool EntityManager::exist(EntityName name, ClusterName cluster)
{
    return _entities.exist(name, cluster);
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

std::vector<Signature> &EntityManager::_getSignatureList()
{
    return this->_entities.getSignatureList();
}

const Signature &EntityManager::_getSignature(Entity entity)
{
    return this->_entities.getSignature(entity);
}

EntityRegister &EntityManager::_getEntityRegister()
{
    return this->_entities;
}

Entity EntityManager::getId(EntityName name)
{
    return this->_entities.getId(name);
}

std::size_t EntityManager::getClusterSize(ClusterName cluster)
{
    return this->_entities.getClusterSize(cluster);
}
