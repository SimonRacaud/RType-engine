/*
** EPITECH PROJECT, 2021
** RType
** File description:
** StateMachineSystem
*/

#include "StateMachineSystem.hpp"

using namespace System;

StateMachineSystem::StateMachineSystem()
{
	this->setRequirements<Engine::Position, Engine::Velocity, Component::EntityMask>();
}

void StateMachineSystem::run(const std::vector<Engine::Entity> &entities)
{
	for (Engine::Entity e : entities) {
		Component::StateMachine &machine = GET_COMP_M.get<Component::StateMachine>(e);

		machine._stateEvents[machine._currentState].operator()(e);
		switch (machine._currentState) {
			case Component::StateMachine::IDLE:
				machine._currentState = Component::StateMachine::MOVE;
				break;
			case Component::StateMachine::MOVE:
				machine._currentState = Component::StateMachine::ATTACK;
				break;
			case Component::StateMachine::ATTACK:
				machine._currentState = Component::StateMachine::IDLE;
				break;
			default:
				break;
		}
	}
}
