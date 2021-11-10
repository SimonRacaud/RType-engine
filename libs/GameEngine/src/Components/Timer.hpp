/*
** EPITECH PROJECT, 2021
** RType
** File description:
** Timer
*/

#ifndef TIMER_HPP_
#define TIMER_HPP_

#include "BaseComponent/BaseComponent.hpp"
#include <functional>
#include <chrono>
#include <tuple>
#include "global.hpp"

namespace Engine {
	class Timer : public BaseComponent<Timer> {
		public:
			Timer(float time, const std::shared_ptr<std::function<void(Entity)>> factory, bool countdown = true)
				: _countdown(countdown), _maxTime(time), _currentTime(time), _eventFactory(factory) {}
			virtual ~Timer() = default;

			/**
			 * @brief Resets the timer to zero
			 * 
			 */
			inline void reset() { _currentTime = _maxTime; }

			bool _countdown;
			float _maxTime;
			float _currentTime;
			float _startTime;
			std::shared_ptr<std::function<void(Entity)>> _eventFactory;
	};
}

#endif /* !TIMER_HPP_ */
