/*
** EPITECH PROJECT, 2021
** RType
** File description:
** StateMachine
*/

#include "StateMachine.hpp"

StateMachine::StateMachine(IEnemyApi *enemyApi) 
	: _currentState(IDLE), _enemyApi(enemyApi)
{
}

StateMachine::~StateMachine()
{
}

void StateMachine::run()
{

	switch (_currentState) {
		case StateMachine::IDLE:
			_enemyApi->idle(_enemyApi);
			_currentState = StateMachine::MOVE;
			break;
		case StateMachine::MOVE:
			_enemyApi->move(_enemyApi);
			_currentState = StateMachine::ATTACK;
			break;
		case StateMachine::ATTACK:
			_enemyApi->attack(_enemyApi);
			_currentState = StateMachine::IDLE;
			break;
		default:
			break;
	}
}