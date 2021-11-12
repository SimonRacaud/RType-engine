/*
** EPITECH PROJECT, 2021
** RType
** File description:
** SfmlApiManager
*/

#include "SfmlApiManager.hpp"

SfmlApiManager::SfmlApiManager() : _windowManager(std::make_shared<WindowManager>())
{
}

SfmlApiManager::~SfmlApiManager()
{
}

extern "C" {
    EXPORTED SfmlApiManager *initApi();
	SfmlApiManager *initApi() {
		return new SfmlApiManager();
	}

	EXPORTED void closeApi(SfmlApiManager *ptr);
	void closeApi(SfmlApiManager *ptr) {
		delete ptr;
	}
}