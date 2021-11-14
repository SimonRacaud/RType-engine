/*
** EPITECH PROJECT, 2021
** RType
** File description:
** EnemyLoader
*/

#include "EnemyLoader.hpp"

IEnemyApi *loadEnemyApi(const std::string &path)
{
	IEnemyApi *ptr = DLLoader<IEnemyApi>::getEntryPoint(path);
	
	if (ptr == nullptr) {
		throw Engine::RuntimeException("Could not load enemy lib");
	}
	return ptr;
}

void closeEnemyApi(IEnemyApi *ptr)
{
	if (ptr)
		delete ptr;
}