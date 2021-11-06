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

namespace Engine {
	class Timer : public BaseComponent<Timer> {
		public:
			Timer(float time, EventCallbackSignature callback, Event::IEvent *e) 
				: _maxTime(time), _currentTime(time), _callback(callback), _callbackEvent(e) {}
			virtual ~Timer() = default;

			/**
			 * @brief Resets the timer to zero
			 * 
			 */
			inline void reset() { _currentTime = _maxTime; }

			float _maxTime;
			float _currentTime;
			EventCallbackSignature _callback;
			Event::IEvent *_callbackEvent;

	};
}

#endif /* !TIMER_HPP_ */
