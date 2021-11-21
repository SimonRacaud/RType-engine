/*
** EPITECH PROJECT, 2021
** RType
** File description:
** StateMachine
*/

#include "StateMachine.hpp"
#include "PhysicController/PhysicController.hpp"

StateMachine::StateMachine(IEnemyApi *enemyApi) 
	: _currentState(IDLE), _enemyApi(enemyApi)
{
}

StateMachine::~StateMachine()
{
}

void StateMachine::run()
{
    /// REFRESH POSITION
    Engine::Position &position = this->_enemyApi->getPosition();
    Engine::Velocity &velocity = this->_enemyApi->getVelocity();
    PhysicController::Update(velocity, position, _lastPhysicRefresh);

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

void StateMachine::enable(uint32_t networkId)
{
    this->_networkId = networkId;
    this->_enable = true;
}

bool StateMachine::isEnable() const
{
    return _enable;
}
