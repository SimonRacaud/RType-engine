/*
** EPITECH PROJECT, 2021
** RType
** File description:
** SfmlApiManager
*/

#include "SfmlApiManager.hpp"

SfmlApiManager::SfmlApiManager() 
	: _windowManager(std::make_shared<WindowManager>()), _animationManager(std::make_shared<AnimationManager>()), _musicManager(std::make_shared<MusicManager>()), _soundManager(std::make_shared<SoundManager>())
{
}

SfmlApiManager::~SfmlApiManager()
{
}

extern "C" {
	EXPORTED SfmlApiManager *initApi() {
		return new SfmlApiManager();
	}

	EXPORTED void closeApi(SfmlApiManager *ptr) {
		delete ptr;
	}
}