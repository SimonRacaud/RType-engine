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
void chargeShot(const ChargeShot *e);
void releaseShot(const ReleaseChargedShot *e);

class ShootEventsManager {
	public:
		ShootEventsManager();
		~ShootEventsManager() = default;
};

#endif /* !SHOOTEVENTSMANAGER_HPP_ */
