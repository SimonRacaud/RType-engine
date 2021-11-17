/*
** EPITECH PROJECT, 2021
** RType
** File description:
** MoveHandler
*/

#ifndef MoveHandler_HPP_
#define MoveHandler_HPP_

#include "EngineCore.hpp"
#include "Event/MoveEvents/MoveEvents.hpp"

void moveUp(const MoveUp *e);
void moveDown(const MoveDown *e);
void moveLeft(const MoveLeft *e);
void moveRight(const MoveRight *e);
void notMovingY(const NotMovingY *e);
void notMovingX(const NotMovingX *e);
class MoveHandler {
	public:
		MoveHandler();
		~MoveHandler() = default;
};

#endif /* !MoveHandler_HPP_ */
