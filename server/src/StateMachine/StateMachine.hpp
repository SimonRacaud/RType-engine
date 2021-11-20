/*
** EPITECH PROJECT, 2021
** RType
** File description:
** StateMachine
*/

#ifndef STATEMACHINE_HPP_
#define STATEMACHINE_HPP_

#include "IEnemyApi.hpp"
#include "utils/timeDef.hpp"

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

        void enable(uint32_t networkId);
        [[nodiscard]] bool isEnable() const;

		STATE _currentState;
		IEnemyApi *_enemyApi;
		uint32_t _networkId{0};
        bool _enable{false};
        TimePoint _lastPhysicRefresh{};
};

#endif /* !STATEMACHINE_HPP_ */
