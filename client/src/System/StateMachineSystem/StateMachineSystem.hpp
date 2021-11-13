/*
** EPITECH PROJECT, 2021
** RType
** File description:
** StateMachineSystem
*/

#ifndef STATEMACHINESYSTEM_HPP_
#define STATEMACHINESYSTEM_HPP_

#include "EngineCore.hpp"
#include "Component/StateMachine.hpp"
#include "Component/EntityMask.hpp"

namespace System {
	class StateMachineSystem : Engine::AbstractSystem<StateMachineSystem> {
		public:
			StateMachineSystem();
			virtual ~StateMachineSystem() = default;

			void run(const std::vector<Engine::Entity> &entities);
	};
}
#endif /* !STATEMACHINESYSTEM_HPP_ */
