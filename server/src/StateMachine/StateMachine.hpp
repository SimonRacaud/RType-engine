/*
** EPITECH PROJECT, 2021
** RType
** File description:
** StateMachine
*/

#ifndef STATEMACHINE_HPP_
#define STATEMACHINE_HPP_

#include "IEnemyApi.hpp"

class StateMachine {
	public:
		StateMachine(IEnemyApi *enemyApi);
		~StateMachine();

		enum STATE {
			IDLE,
			MOVE,
			ATTACK
		};
		void run();

		STATE _currentState;
		IEnemyApi *_enemyApi;
};

#endif /* !STATEMACHINE_HPP_ */
