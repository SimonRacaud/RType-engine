/*
** EPITECH PROJECT, 2021
** RType
** File description:
** Timer
*/

#ifndef BASE_TIMER_HPP
#define BASE_TIMER_HPP

#include "BaseComponent/BaseComponent.hpp"
#include <functional>
#include <chrono>
#include <tuple>

namespace Engine {
	class BaseTimer : public BaseComponent<BaseTimer> {
		public:
			BaseTimer(float maxTime) : _maxTime(maxTime), _currentTime(maxTime) {}
			virtual ~BaseTimer() = default;

			/**
			 * @brief Resets the timer to zero
			 * 
			 */
			inline void reset() { _currentTime = _maxTime; }
			virtual void exec() {}

			float _maxTime;
			float _currentTime;
	};
}

#endif /* !BASE_TIMER_HPP */
