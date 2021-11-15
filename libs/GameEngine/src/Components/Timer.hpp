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
			Timer(Time time, const std::function<void(Entity)> factory, bool countdown = true, Time interval = std::chrono::milliseconds(10))
				: _countdown(countdown), _maxTime(time), _currentTime(time), _interval(interval), _startTime(Clock::now()), _eventFactory(factory) {}
			virtual ~Timer() = default;

			bool _countdown;
			Time _maxTime;
			Time _currentTime;
			Time _interval;
			TimePoint _startTime;
			std::function<void(Entity)> _eventFactory;
	};
}

#endif /* !TIMER_HPP_ */
