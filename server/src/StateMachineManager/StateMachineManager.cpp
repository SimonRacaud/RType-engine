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
	_loadedEnemies.push_back(StateMachine(ptr));
	_apiPaths.push_back(path);
	return ptr;
}

void StateMachineManager::loadAllApiInFolder(const std::string folder)
{
	//TODO if we have time;
	(void)folder;
}

void StateMachineManager::closeEnemyApi(IEnemyApi *ptr)
{
	std::vector<StateMachine>::iterator machine = getMachineFromApi(ptr);
	auto index = std::distance(_loadedEnemies.begin(), machine);

	DLLoader<IEnemyApi>::getClosePoint(_apiPaths[index], "closeApi", ptr);
}

void StateMachineManager::setMachineNetworkId(const IEnemyApi *ptr, uint32_t networkId)
{
	try {
		StateMachine enemy = *getMachineFromApi(ptr);
		enemy._networkId = networkId;
	} catch (Engine::RuntimeException &e) {
		std::cerr << "Could not set Network ID for enemy because ptr does not exists" << std::endl;
	}
}

std::vector<StateMachine>::iterator StateMachineManager::getMachineFromApi(const IEnemyApi *ptr)
{
	auto machine = _loadedEnemies.begin();

	while (machine != _loadedEnemies.end() && (*machine)._enemyApi != ptr)
		machine++;
	if (machine == _loadedEnemies.end())
		throw Engine::RuntimeException("Not machine with this api pointer");
	return machine;
}

void StateMachineManager::runAllMachines()
{
	for (auto machine : _loadedEnemies) {
		machine.run();
	}
}

std::vector<Engine::Position> StateMachineManager::retreivePosComponents()
{
	std::vector<Engine::Position> allPos;

	for (auto machines : _loadedEnemies)
		allPos.push_back(machines._enemyApi->getPosition());
	return allPos;
}

std::vector<Engine::Velocity> StateMachineManager::retreiveVelComponents()
{
	std::vector<Engine::Velocity> allVel;

	for (auto machines : _loadedEnemies)
		allVel.push_back(machines._enemyApi->getVelocity());
	return allVel;
}

std::vector<Component::Health> StateMachineManager::retreiveHealthComponents()
{
	std::vector<Component::Health> allHealth;

	for (auto machines : _loadedEnemies)
		allHealth.push_back(machines._enemyApi->getHealth());
	return allHealth;
}

std::vector<std::pair<Component::AnimationInfo, std::pair<float, float>>> StateMachineManager::retreiveBasicComponents()
{
	std::vector<std::pair<Component::AnimationInfo, std::pair<float, float>>> allPairs;

	for (auto machines : _loadedEnemies) {
		allPairs.push_back(std::make_pair<Component::AnimationInfo, std::pair<float, float>>(machines._enemyApi->getAnimInfo(), machines._enemyApi->getHitboxSize()));
	}
	return allPairs;
}


std::vector<uint32_t> StateMachineManager::retreiveNetworkId()
{
	std::vector<uint32_t> allId;

	for (auto machines : _loadedEnemies)
		allId.push_back(machines._networkId);
	return allId;
}

std::pair<Component::AnimationInfo, std::pair<float, float>> StateMachineManager::retreiveBasicComponents(const IEnemyApi *ptr)
{
	return std::make_pair<Component::AnimationInfo, std::pair<float, float>>(ptr->getAnimInfo(), ptr->getHitboxSize());
}