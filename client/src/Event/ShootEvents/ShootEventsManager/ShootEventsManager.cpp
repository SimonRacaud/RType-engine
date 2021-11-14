/*
** EPITECH PROJECT, 2021
** RType
** File description:
** ShootEventsManager
*/

#include "ShootEventsManager.hpp"

ShootEventsManager::ShootEventsManager()
{
	GET_EVENT_REG.registerCallback(std::function<void(const ShootOnce *e)>(shootOnce));
}

void shootOnce(const ShootOnce *e)
{
	auto pos = GET_COMP_M.get<Engine::Position>(e->_entity);
	
	Bullet b(1, vector2D(pos.x, pos.y));
}