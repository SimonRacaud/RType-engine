/*
** EPITECH PROJECT, 2021
** RType
** File description:
** MoveSystem
*/

#include "MoveHandler.hpp"

MoveHandler::MoveHandler()
{
	GET_EVENT_REG.registerCallback(std::function<void(const MoveUp *)>(moveUp));
	GET_EVENT_REG.registerCallback(std::function<void(const MoveDown *)>(moveDown));
	GET_EVENT_REG.registerCallback(std::function<void(const MoveLeft *)>(moveLeft));
	GET_EVENT_REG.registerCallback(std::function<void(const MoveRight *)>(moveRight));
}

void moveUp(const MoveUp *e)
{
	auto [pos, velocity] = GET_COMP_M.getList<Engine::Position, Engine::Velocity>(e->_entityId);
	pos.y += velocity.y;
}

void moveDown(const MoveDown *e)
{
	auto [pos, velocity] = GET_COMP_M.getList<Engine::Position, Engine::Velocity>(e->_entityId);
	pos.y -= velocity.y;
}

void moveLeft(const MoveLeft *e)
{
	auto [pos, velocity] = GET_COMP_M.getList<Engine::Position, Engine::Velocity>(e->_entityId);
	pos.x -= velocity.x;
}

void moveRight(const MoveRight *e)
{
	auto [pos, velocity] = GET_COMP_M.getList<Engine::Position, Engine::Velocity>(e->_entityId);
	pos.x += velocity.x;
}

