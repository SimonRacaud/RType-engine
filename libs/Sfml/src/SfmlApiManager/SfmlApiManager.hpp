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
#include "AudioManager/MusicManager/MusicManager.hpp"
#include "AudioManager/SoundManager/SoundManager.hpp"
#include "EventManager/EventManager.hpp"
#include "SpriteManager/SpriteManager.hpp"
#include "TextManager/TextManager.hpp"
#include <memory>

class SfmlApiManager {
	public:
		SfmlApiManager();
		~SfmlApiManager();

		std::shared_ptr<WindowManager> _windowManager;
		std::shared_ptr<AnimationManager> _animationManager;
		std::shared_ptr<MusicManager> _musicManager;
		std::shared_ptr<SoundManager> _soundManager;
		std::shared_ptr<EventManager> _eventManager;
		std::shared_ptr<SpriteManager> _spriteManager;
		std::shared_ptr<TextManager> _textManager;
		private:
};

#endif /* !SfmlApiManager_HPP_ */
