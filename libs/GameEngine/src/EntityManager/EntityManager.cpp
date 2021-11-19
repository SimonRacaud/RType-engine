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

    SHOW_DEBUG("Will clean " + std::to_string(list.size()) + " entities:");
    for (Entity entity : list) {
        this->remove(entity);
    }
    SHOW_DEBUG("Entity: " + std::to_string(list.size()) + " entities removed.");
}

Entity EntityManager::create(EntityDestructor destructor, ClusterName cluster,
    EntityName name, bool setNetworkId)
{
    if (this->exist(name)) {
        throw InvalidParameterException("EntityManager::create entity name already used.");
    }
    return _entities.create(cluster, name, destructor, setNetworkId);
}

void EntityManager::remove(Entity entity)
{
    Signature const &signature = this->_entities.getSignature(entity);

    // Hey Entity Register, remove [entity] from your register
    _entities.destroyEntity(entity); // launch destructor callback
    _entities.remove(entity);
    // Hey systems! Remove [entity] from your managed entity lists
    GET_SYS_M._onEntityRemoved(entity);
    // Hey BaseComponent Registers! Remove the instances of the Components of [entity].
    this->_removeEntityComponents(entity, signature);
}

void EntityManager::remove(EntityName name)
{
    while (true) {
        try {
            Signature const &signature =
                this->_entities.getSignature(this->_entities.getId(name));

            // Hey Entity Register, remove [entity] from your register
            _entities.destroyEntity(this->getId(name)); // launch destructor callback
            Entity entity = _entities.remove(name);
            // Hey systems! Remove [entity] from your managed entity lists
            GET_SYS_M._onEntityRemoved(entity);
            // Hey BaseComponent Registers! Remove the instances of the Components of [entity].
            this->_removeEntityComponents(entity, signature);
        } catch (NotFoundException const &) {
            break;
        }
    }
}

void EntityManager::remove(ClusterName cluster)
{
    vector<Entity> const &entities = this->_entities.getClusterEntityList(cluster);

    for (Entity entity : entities) {
        _entities.destroyEntity(entity); // launch destructor callback

        Signature const &signature = this->_entities.getSignature(entity);
        // Hey BaseComponent Registers! Remove the instances of the Components of [entity].
        this->_removeEntityComponents(entity, signature);
    }
    // Hey Entity Register, remove [entity] from your register
    _entities.remove(entities);
    for (Entity entity : entities) {
        // Hey systems! Remove [entity] from your managed entity lists
        GET_SYS_M._onEntityRemoved(entity);
    }
}

bool EntityManager::exist(Entity entity)
{
    return _entities.exist(entity);
}

bool EntityManager::exist(EntityName name)
{
    return _entities.exist(name);
}

Entity EntityManager::getId(NetworkId id)
{
    return _entities.getId(id);
}

void EntityManager::setNetworkId(Entity entity)
{
    _entities.setNetworkId(entity);
}

NetworkId EntityManager::getNetworkId()
{
    return _entities.getNetworkId();
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

NetworkId EntityManager::getNetworkId(Entity entity)
{
    return _entities.getNetworkId(entity);
}

ClusterName EntityManager::getCluster(Entity entity)
{
    return _entities.getCluster(entity);
}

void EntityManager::_removeEntityComponents(Entity entity,
    Signature const &signature)
{
    std::array<shared_ptr<IComponentTypeRegister>, MAX_COMPONENT_TYPE> &registers
        = GET_COMP_M._componentRegisters;

    for (size_t idx = 0; idx < signature.size(); idx++) {
        if (signature[idx] && registers[idx] != nullptr) {
            try {
                registers[idx]->remove(entity);
            } catch (InvalidParameterException const &) {
                std::cerr << "EntityManager::remove oops that error mustn't append" << std::endl;
            }
        }
    }
}