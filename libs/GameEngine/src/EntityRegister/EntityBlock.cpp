/*
** EPITECH PROJECT , 2021
** EntityBlock
** File description:
** \file EntityBlock.cpp
** \author simon
** \brief
** \date 01/11/2021
*/

#include "EntityBlock.hpp"

using namespace Engine;

EntityBlock::EntityBlock(Entity entity, ClusterName cluster, EntityName name,
    EntityDestructor destructor)
    : _entity(entity), _name(name), _cluster(cluster), _destructor(destructor)
{
    this->removed = false;
}

EntityBlock::EntityBlock(const EntityBlock &block)
    : _entity(block._entity), _name(block._name), _cluster(block._cluster),
      _destructor(block._destructor), _networkId(block._networkId),
      removed(block.removed)
{
}

bool EntityBlock::operator==(EntityName name)
{
    return name == _name;
}

bool EntityBlock::operator==(Entity entity)
{
    return entity == _entity;
}

bool EntityBlock::operator==(ClusterName cluster)
{
    return cluster == _cluster;
}

Entity EntityBlock::getEntity() const
{
    return _entity;
}

void EntityBlock::setEntity(Entity entity)
{
    this->_entity = entity;
}

EntityName EntityBlock::getName() const
{
    return _name;
}

ClusterName EntityBlock::getCluster() const
{
    return _cluster;
}

void EntityBlock::destroy()
{
    if (this->_destructor != nullptr) {
        this->_destructor(_entity, _name, _cluster);
    }
}

void EntityBlock::setNetworkId(NetworkId id)
{
    this->_networkId = id;
}

NetworkId EntityBlock::getNetworkId() const
{
    return _networkId;
}

EntityBlock &EntityBlock::operator=(EntityBlock const& block)
{
    _entity = block.getEntity();
    _name = block.getName();
    _cluster = block.getCluster();
    _destructor = block._destructor;
    _networkId = block._networkId;
    this->removed = block.removed;
    return *this;
}
