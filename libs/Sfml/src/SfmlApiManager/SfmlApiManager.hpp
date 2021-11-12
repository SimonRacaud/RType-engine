/*
** EPITECH PROJECT, 2021
** RType
** File description:
** SfmlApiManager
*/

#ifndef SfmlApiManager_HPP_
#define SfmlApiManager_HPP_

#include "exported.h"
#include "WindowManager/WindowManager.hpp"
#include "AnimationManager/AnimationManager.hpp"
#include <memory>

class SfmlApiManager {
	public:
		SfmlApiManager();
		~SfmlApiManager();

		std::shared_ptr<WindowManager> _windowManager;
		private:
};

#endif /* !SfmlApiManager_HPP_ */
