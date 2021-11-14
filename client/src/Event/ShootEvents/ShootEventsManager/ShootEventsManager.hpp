/*
** EPITECH PROJECT, 2021
** RType
** File description:
** ShootEventsManager
*/

#ifndef SHOOTEVENTSMANAGER_HPP_
#define SHOOTEVENTSMANAGER_HPP_

#include "EngineCore.hpp"
#include "Event/ShootEvents/ShootEvents.hpp"
#include "Entities/Bullet/Bullet.hpp"

void shootOnce(const ShootOnce *e);

class ShootEventsManager {
	public:
		ShootEventsManager();
		~ShootEventsManager() = default;
};

#endif /* !SHOOTEVENTSMANAGER_HPP_ */
