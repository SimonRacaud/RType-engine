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
	GET_EVENT_REG.registerCallback(std::function<void(const NotMoving *)>(notMoving));
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

void notMoving(const NotMoving *e)
{
	Engine::Velocity &velocity = GET_COMP_M.get<Engine::Velocity>(e->_entityId);
	if (velocity.x > 0) {
		velocity.x -= 0.4f;
	} else if (velocity.x < 0) {
		velocity.x += 0.4f;
	}
	if (velocity.y > 0) {
		velocity.y -= 0.4f;
	} else if (velocity.y < 0) {
		velocity.y += 0.4f;
	}
}
