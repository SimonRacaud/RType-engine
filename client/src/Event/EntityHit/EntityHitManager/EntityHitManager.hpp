/*
** EPITECH PROJECT, 2021
** RType
** File description:
** EntityHitManager
*/

#ifndef ENTITYHITMANAGER_HPP_
#define ENTITYHITMANAGER_HPP_

#include "Event/EntityHit/EntityHitEvents.hpp"
#include "Exception/InvalidTypeException.hpp"


void entityHit(const EntityHit *e);

class EntityHitManager {
	public:
		EntityHitManager();
		~EntityHitManager() = default;

};

#endif /* !ENTITYHITMANAGER_HPP_ */
