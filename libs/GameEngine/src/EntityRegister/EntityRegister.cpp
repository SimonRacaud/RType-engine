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
}

std::vector<Signature> &EntityRegister::getSignatureList()
{
    return _signatures;
}

const Signature &EntityRegister::getSignature(Entity entity) const
{
    if (!this->exist(entity)) {
        throw NotFoundException("Entity not found");
    }
    return _signatures[entity];
}

Entity EntityRegister::create(ClusterName cluster, EntityName name,
    EntityDestructor destructor, bool setNetworkId)
{
    // TODO : offset
    Entity entity = 0;

    //    if (_freeEntities.empty()) {
    //        entity = static_cast<Entity>(_signatures.size());
    //        _signatures.emplace_back();
    //    } else {
    //        entity = _freeEntities.back();
    //        _freeEntities.pop_back();
    //        _signatures[entity].reset();
    //    }
    return entity;
}

void EntityRegister::remove(Entity entity)
{
    // TODO
    //    if (std::find(_freeEntities.begin(), _freeEntities.end(), entity) !=
    //    _freeEntities.end()) {
    //        throw std::invalid_argument("EntityRegister::remove Entity
    //        already removed.");
    //    }
    //    _freeEntities.push_back(entity);
}

void EntityRegister::remove(EntityName name)
{
    /// TODO
}

void EntityRegister::remove(ClusterName cluster)
{
    // TODO
}

bool EntityRegister::exist(Entity entity) const
{
    // TODO
    //    if (std::find(_freeEntities.begin(), _freeEntities.end(), entity) !=
    //    _freeEntities.end()) {
    //        return false;
    //    }
    //    if (_signatures.size() <= entity) {
    //        return false;
    //    }
    return true;
}

bool EntityRegister::exist(EntityName name, ClusterName cluster) const
{
    // TODO
    return false;
}

bool EntityRegister::exist(ClusterName cluster) const
{
    // TODO
    return false;
}

Entity EntityRegister::getId(EntityName name) const
{
    // TODO
    return 0;
}

Entity EntityRegister::getId(NetworkId networkId) const
{
    // TODO
    return 0;
}

size_t EntityRegister::getClusterSize(ClusterName cluster) const
{
    // TODO
    return 0;
}

void EntityRegister::setNetworkId(Entity entity, NetworkId id)
{
    // TODO
}
