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
    try {
        Engine::Velocity &velocity = GET_COMP_M.get<Engine::Velocity>(e->_entityId);
        velocity.y = -e->_speed;
    } catch (std::exception const &e) {
        std::cerr << "MoveHandler::moveUp " << e.what() << std::endl;
    }
}

void moveDown(const MoveDown *e)
{
    try {
        Engine::Velocity &velocity = GET_COMP_M.get<Engine::Velocity>(e->_entityId);
        velocity.y = e->_speed;
    } catch (std::exception const &e) {
        std::cerr << "MoveHandler::moveDown " << e.what() << std::endl;
    }
}

void moveLeft(const MoveLeft *e)
{
     try {
        Engine::Velocity &velocity = GET_COMP_M.get<Engine::Velocity>(e->_entityId);
        velocity.x = -e->_speed;
     } catch (std::exception const &e) {
         std::cerr << "MoveHandler::moveLeft " << e.what() << std::endl;
     }
}

void moveRight(const MoveRight *e)
{
    try {
        Engine::Velocity &velocity = GET_COMP_M.get<Engine::Velocity>(e->_entityId);
        velocity.x = e->_speed;
    } catch (std::exception const &e) {
        std::cerr << "MoveHandler::moveRight " << e.what() << std::endl;
    }
}

void notMovingY(const NotMovingY *e)
{
    try {
        Engine::Velocity &velocity = GET_COMP_M.get<Engine::Velocity>(e->_entityId);

        velocity.y = 0.3f;
    } catch (std::exception const &e) {
        std::cerr << "MoveHandler::notMovingY " << e.what() << std::endl;
    }
}

void notMovingX(const NotMovingX *e)
{
    try {
        Engine::Velocity &velocity = GET_COMP_M.get<Engine::Velocity>(e->_entityId);

        velocity.x = 0.3f;
    } catch (std::exception const &e) {
        std::cerr << "MoveHandler::notMovingX " << e.what() << std::endl;
    }
}
