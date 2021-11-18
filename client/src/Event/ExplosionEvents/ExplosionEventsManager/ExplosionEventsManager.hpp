/*
** EPITECH PROJECT, 2021
** RType
** File description:
** ExplosionEventsManager
*/

#ifndef EXPLOSIONEVENTSMANAGER_HPP_
#define EXPLOSIONEVENTSMANAGER_HPP_

#include "GameCore.hpp"
#include "ExplosionEvents.hpp"

void bulletExplosion(const BulletExplosion *e);

class ExplosionEventsManager {
	public:
		ExplosionEventsManager();
		~ExplosionEventsManager() = default;
};

#endif /* !EXPLOSIONEVENTSMANAGER_HPP_ */
