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
    this->_destructor(_entity, _name, _cluster);
}

void EntityBlock::setNetworkId(NetworkId id)
{
    this->_networkId = id;
}

NetworkId EntityBlock::getNetworkId() const
{
    return _networkId;
}