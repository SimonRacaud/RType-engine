/*
** EPITECH PROJECT, 2021
** RType
** File description:
** EntityRemoveManager
*/

#ifndef ENTITYREMOVEMANAGER_HPP_
#define ENTITYREMOVEMANAGER_HPP_

#include "GameCore.hpp"
#include "EntityRemoveEvent.hpp"

void entityRemove(const EntityRemoveEvent *e);

class EntityRemoveManager {
	public:
		EntityRemoveManager();
		~EntityRemoveManager() = default;
};

#endif /* !ENTITYREMOVEMANAGER_HPP_ */