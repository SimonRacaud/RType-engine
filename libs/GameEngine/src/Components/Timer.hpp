/*
** EPITECH PROJECT, 2021
** RType
** File description:
** Timer
*/

#ifndef TIMER_HPP_
#define TIMER_HPP_

#include "BaseTimer.hpp"
#include "global.hpp"

namespace Engine {
	template<class EventType, class... EventArgs>
	class Timer : public BaseTimer {
		public:
			template<class... Args>
			Timer(float time, Args&&... args)
				: BaseTimer(time), _args(std::forward<Args>(args)...) {}
			virtual ~Timer() = default;

			virtual void exec() override {
				GET_EVENT_REG.registerEvent<EventType>(std::forward<EventArgs>(_args));
			}
			std::tuple<EventArgs...> _args;
	};
}

#endif /* !TIMER_HPP_ */
