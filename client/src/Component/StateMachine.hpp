/*
** EPITECH PROJECT, 2021
** RType
** File description:
** StateMachine
*/

#ifndef STATEMACHINE_HPP_
#define STATEMACHINE_HPP_

#include "EngineCore.hpp"

namespace Component {
	class StateMachine : public Engine::BaseComponent<StateMachine> {
		public:
			StateMachine(const float &moveSpeed, const bool canShoot, const std::vector<std::function<void(Engine::Entity)>> &stateEvents) 
			: _currentState(IDLE), _moveSpeed(moveSpeed), _canShootBullets(canShoot), _stateEvents(stateEvents) {}
			virtual ~StateMachine() = default;

			enum STATE {
				IDLE,
				MOVE,
				ATTACK
			};

			STATE _currentState;
			float _moveSpeed;
			bool _canShootBullets;
			std::vector<std::function<void(Engine::Entity)>> _stateEvents;
	};
}

#endif /* !STATEMACHINE_HPP_ */
