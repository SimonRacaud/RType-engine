/*
** EPITECH PROJECT, 2021
** RType
** File description:
** StateMachineManager
*/

#ifndef STATEMACHINEMANAGER_HPP_
#define STATEMACHINEMANAGER_HPP_

#include "StateMachine/StateMachine.hpp"

class StateMachineManager {
	public:
		StateMachineManager();
		~StateMachineManager();

	protected:
		std::vector<StateMachine> _loadedEnemies;
	private:
};

#endif /* !STATEMACHINEMANAGER_HPP_ */
