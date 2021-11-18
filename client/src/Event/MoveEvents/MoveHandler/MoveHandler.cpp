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
	GET_EVENT_REG.registerCallback(std::function<void(const NotMovingY *)>(notMovingY));
	GET_EVENT_REG.registerCallback(std::function<void(const NotMovingX *)>(notMovingX));
}

void moveUp(const MoveUp *e)
{
	Engine::Velocity &velocity = GET_COMP_M.get<Engine::Velocity>(e->_entityId);
	velocity.y = -e->_speed;
}

void moveDown(const MoveDown *e)
{
	Engine::Velocity &velocity = GET_COMP_M.get<Engine::Velocity>(e->_entityId);
	velocity.y = e->_speed;
}

void moveLeft(const MoveLeft *e)
{
	Engine::Velocity &velocity = GET_COMP_M.get<Engine::Velocity>(e->_entityId);
	velocity.x = -e->_speed;
}

void moveRight(const MoveRight *e)
{
	Engine::Velocity &velocity = GET_COMP_M.get<Engine::Velocity>(e->_entityId);
	velocity.x = e->_speed;
}

void notMovingY(const NotMovingY *e)
{
	Engine::Velocity &velocity = GET_COMP_M.get<Engine::Velocity>(e->_entityId);

	velocity.y = 0.3f;
}

void notMovingX(const NotMovingX *e)
{
	Engine::Velocity &velocity = GET_COMP_M.get<Engine::Velocity>(e->_entityId);

	velocity.x = 0.3f;
}
