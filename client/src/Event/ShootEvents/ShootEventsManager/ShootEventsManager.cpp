/*
** EPITECH PROJECT, 2021
** RType
** File description:
** ShootEventsManager
*/

#include "ShootEventsManager.hpp"

ShootEventsManager::ShootEventsManager()
{
}

void shootOnce(const ShootOnce *e)
{
	auto pos = GET_COMP_M.get<Engine::Position>(e->_entity);
	
	Bullet b(vector2D(pos.x, pos.y));
}