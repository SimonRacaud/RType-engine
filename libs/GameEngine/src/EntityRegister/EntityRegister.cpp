/*
** EPITECH PROJECT, 2021
** GameEngine
** File description:
** 27/05/2021 EntityRegister.cpp.cc
*/

#include "EntityRegister.hpp"

using namespace Engine;

void EntityRegister::allocate(std::size_t size)
{
    _freeEntities.resize(size);
    std::iota(std::begin(_freeEntities), std::end(_freeEntities), 0);
    _signatures.resize(size);
    _bookedEntities.resize(size);
}

std::vector<Signature> &EntityRegister::getSignatureList()
{
    return _signatures;
}

const Signature &EntityRegister::getSignature(Entity entity) const
{
    if (!this->exist(entity)) {
        throw NotFoundException("EntityRegister::getSignature Entity not found");
    }
    return _signatures[entity];
}

Entity EntityRegister::create(ClusterName cluster, EntityName name,
    EntityDestructor destructor, bool setNetworkId)
{
    Entity entity = 0;

    if (_freeEntities.empty()) {
        entity = static_cast<Entity>(_signatures.size());
        _signatures.emplace_back();
        _bookedEntities.emplace_back(EntityBlock(entity, cluster, name, destructor));
    } else {
        entity = _freeEntities.back();
        _freeEntities.pop_back();
        _signatures[entity].reset();
        _bookedEntities[entity] = EntityBlock(entity, cluster, name, destructor);
    }
    if (setNetworkId) {
        _bookedEntities[entity].setNetworkId(_networkIdRegister.reserveId());
    }
    _bookedEntities[entity].removed = false;
    SHOW_DEBUG("Entity: create id=" + std::to_string(entity));
    return entity;
}

void EntityRegister::remove(Entity entity)
{
    SHOW_DEBUG("Entity: remove id=" + std::to_string(entity));
    if (std::find(_freeEntities.begin(), _freeEntities.end(), entity) !=
        _freeEntities.end()) {
        throw NotFoundException("EntityRegister::remove Entity already removed.");
    }
    _freeEntities.push_back(entity);
    _bookedEntities[entity].removed = true;
}

Entity EntityRegister::remove(EntityName name)
{
    Entity entity = this->getId(name);

    this->remove(entity);
    return entity;
}

vector<Entity> EntityRegister::remove(ClusterName cluster)
{
    vector<Entity> list = this->getClusterEntityList(cluster);

    for (Entity entity : list) {
        this->remove(entity);
    }
    return list;
}

void EntityRegister::remove(const vector<Entity> &list)
{
    for (Entity entity : list) {
        this->remove(entity);
    }
}

bool EntityRegister::exist(Entity entity) const
{
    if (std::find(_freeEntities.begin(), _freeEntities.end(), entity) !=
        _freeEntities.end()) {
        return false;
    }
    if (_signatures.size() <= entity) {
        return false;
    }
    return true;
}

bool EntityRegister::exist(EntityName name) const
{
    try {
        if (name == EntityName::EMPTY) {
            return false;
        }
        return this->getId(name) ? true : true;
    } catch (NotFoundException const &) {}
    return false;
}

Entity EntityRegister::getId(EntityName name) const
{
    if (name == EntityName::EMPTY) {
        throw NotFoundException("EntityRegister::getId Invalid entity name");
    }
    for (auto it = _bookedEntities.begin(); it != _bookedEntities.end(); it++) {
        if (it->removed == false && it->getName() == name) {
            return it->getEntity();
        }
    }
    throw NotFoundException("EntityRegister::getId Entity name not found");
}

Entity EntityRegister::getId(NetworkId networkId) const
{
    if (networkId == NO_NET_ID) {
        throw FatalErrorException("EntityRegister::getId Invalid network id");
    }
    for (auto it = _bookedEntities.begin(); it != _bookedEntities.end(); it++) {
        if (it->removed == false && it->getNetworkId() == networkId) {
            return it->getEntity();
        }
    }
    throw NotFoundException("EntityRegister::getId Network id not found");
}

size_t EntityRegister::getClusterSize(ClusterName cluster) const
{
    return this->getClusterEntityList(cluster).size();
}

void EntityRegister::setNetworkId(Entity entity, NetworkId id)
{
    if (this->exist(entity) == false) {
        throw InvalidParameterException("EntityRegister::setNetworkId the "
                                        "entity doesn't exist");
    }
    try {
        NetworkId entityId = this->getNetworkId(entity); // that method will throw if not found

        throw InvalidParameterException("EntityRegister::setNetworkId "
            "network id " + std::to_string(entityId) + " already assigned.");
    } catch (NotFoundException const &e) {
        (void) e;
    }
    this->_networkIdRegister.reserveId(id);
    this->_bookedEntities[entity].setNetworkId(id);
}

vector<Entity> EntityRegister::getClusterEntityList(ClusterName cluster) const
{
    vector<Entity> list;

    for (auto it = _bookedEntities.begin(); it != _bookedEntities.end(); it++) {
        if (it->removed == false) {
            if (it->getCluster() == cluster) {
                list.push_back(it->getEntity());
            }
        }
    }
    return list;
}

vector<Entity> EntityRegister::getEntityList() const
{
    vector<Entity> list;

    for (auto it = _bookedEntities.begin(); it != _bookedEntities.end(); it++) {
        if (it->removed == false) {
            list.push_back(it->getEntity());
        }
    }
    return list;
}

ClusterName EntityRegister::getCluster(Entity entity) const
{
    if (!this->exist(entity))
        throw NotFoundException("EntityRegister::getCluster entity not found");
    return this->_bookedEntities[entity].getCluster();
}

NetworkId EntityRegister::getNetworkId(Entity entity) const
{
    if (!this->exist(entity))
        throw NotFoundException("EntityRegister::getCluster entity not found");
    NetworkId net = this->_bookedEntities[entity].getNetworkId();

    if (net == NO_NET_ID) {
        throw NotFoundException("EntityRegister::getNetworkId the entity doesn't have an id");
    }
    return net;
}

void EntityRegister::destroyEntity(Entity entity)
{
    if (!this->exist(entity))
        throw NotFoundException("EntityRegister::destroyEntity entity not found");
    _bookedEntities[entity].destroy(); // launch destructor
}
