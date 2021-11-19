/*
** EPITECH PROJECT, 2021
** RType
** File description:
** EntityRemoveManager
*/

#include "EntityRemoveManager.hpp"

EntityRemoveManager::EntityRemoveManager()
{
	GET_EVENT_REG.registerCallback(std::function<void(const EntityRemoveEvent *e)>(entityRemove));
}


void entityRemove(const EntityRemoveEvent *e)
{
    try {
        if (GameCore::networkCore.isMaster()) {
            GameCore::networkCore.destroyEntity(GET_ENTITY_M.getNetworkId(e->_entity));
            GET_ENTITY_M.remove(e->_entity);
        }
    } catch (std::exception const &e) {}
}