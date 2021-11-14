/*
** EPITECH PROJECT, 2021
** RType
** File description:
** ShootEventsManager
*/

#include "ShootEventsManager.hpp"

#include "Component/Shooting.hpp"

ShootEventsManager::ShootEventsManager()
{
	GET_EVENT_REG.registerCallback(std::function<void(const ShootOnce *e)>(shootOnce));
	GET_EVENT_REG.registerCallback(std::function<void(const ChargeShot *e)>(chargeShot));
	GET_EVENT_REG.registerCallback(std::function<void(const ReleaseChargedShot *e)>(releaseShot));
}

void shootOnce(const ShootOnce *e)
{
	auto pos = GET_COMP_M.get<Engine::Position>(e->_entity);
	
	Bullet b(vector2D(pos.x, pos.y));
}

void chargeShot(const ChargeShot *e)
{
	auto &shooting = GET_COMP_M.get<Component::Shooting>(e->_entity);
	
	shooting._chargeStart = std::chrono::steady_clock::now();
	std::cout << "Charging shot\n";
}

void releaseShot(const ReleaseChargedShot *e)
{
	auto now = std::chrono::steady_clock::now();
	auto &shooting = GET_COMP_M.get<Component::Shooting>(e->_entity);
	auto pos = GET_COMP_M.get<Engine::Position>(e->_entity);
	
	auto nb_sec = std::chrono::duration_cast<std::chrono::seconds>(
		now.time_since_epoch() - shooting._chargeStart.time_since_epoch()).count();
	if (nb_sec < 1) {
		Bullet b(1, vector2D(pos.x, pos.y));
	} else {
		//TODO RELEASE CHARGED SHOT
		std::cout << "release shot\n";
	}
}