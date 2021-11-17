/*
** EPITECH PROJECT, 2021
** RType
** File description:
** StateMachineManager
*/

#ifndef STATEMACHINEMANAGER_HPP_
#define STATEMACHINEMANAGER_HPP_

#include "StateMachine/StateMachine.hpp"
#include "Exception/RuntimeException.hpp"
#include "DLLoader/DLLoader.hpp"

class StateMachineManager {
	public:
		StateMachineManager();
		~StateMachineManager();
		
		IEnemyApi *loadEnemyApi(const std::string &path);
		void loadAllApiInFolder(const std::string folder);
		void setMachineNetworkId(const IEnemyApi *ptr, uint32_t networkId);
		void closeEnemyApi(IEnemyApi *ptr);
		void runAllMachines();
		void retreiveSynComponents();
		std::vector<Engine::Position> retreivePosComponents();
		std::vector<Engine::Velocity> retreiveVelComponents();
		std::vector<Component::Health> retreiveHealthComponents();
		std::vector<std::pair<Component::AnimationInfo, std::pair<float, float>>> retreiveBasicComponents();
		StateMachine getMachineFromApi(const IEnemyApi *ptr);
	protected:
		std::vector<StateMachine> _loadedEnemies;
	private:
};

#endif /* !STATEMACHINEMANAGER_HPP_ */
