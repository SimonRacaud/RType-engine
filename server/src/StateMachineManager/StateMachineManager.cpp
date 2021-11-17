/*
** EPITECH PROJECT, 2021
** RType
** File description:
** StateMachineManager
*/

#include "StateMachineManager.hpp"

StateMachineManager::StateMachineManager()
{
}

StateMachineManager::~StateMachineManager()
{
}

IEnemyApi *StateMachineManager::loadEnemyApi(const std::string &path)
{	
	IEnemyApi *ptr = DLLoader<IEnemyApi>::getEntryPoint(path, "initApi");
	
	if (ptr == nullptr) {
		throw Engine::RuntimeException("Could not load enemy lib. Make sure it has an entryPoint called initApi");
	}
	
	return ptr;
}

void StateMachineManager::loadAllApiInFolder(const std::string folder)
{

}

void StateMachineManager::closeEnemyApi(IEnemyApi *ptr)
{

}

void StateMachineManager::setMachineNetworkId(const IEnemyApi *ptr, uint32_t networkId)
{
	try {
		StateMachine enemy = getMachineFromApi(ptr);
		enemy._networkId = networkId;
	} catch (Engine::RuntimeException &e) {
		std::cerr << "Could not set Network ID for enemy because ptr does not exists" << std::endl;
	}
}

StateMachine StateMachineManager::getMachineFromApi(const IEnemyApi *ptr)
{
	auto machine = _loadedEnemies.begin();

	while (machine != _loadedEnemies.end() && (*machine)._enemyApi != ptr)
		machine++;
	if (machine == _loadedEnemies.end())
		throw Engine::RuntimeException("Not machine with this api pointer");
	return (*machine);
}

void StateMachineManager::runAllMachines()
{
	for (auto machine : _loadedEnemies) {
		machine.run();
	}
}

void StateMachineManager::retreiveSynComponents()
{

}

void StateMachineManager::retreiveBasicComponents()
{

}
