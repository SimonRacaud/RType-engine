/*
** EPITECH PROJECT, 2021
** RType
** File description:
** TimerEvent
*/

#ifndef TIMEREVENT_HPP_
#define TIMEREVENT_HPP_

#include "Event/AbstractEvent/AbstractEvent.hpp"
#include <string>

class TimerEvent : Engine::Event::AbstractEvent<TimerEvent> {
	public:
		TimerEvent(std::string &print) : _print(print) {}
		virtual ~TimerEvent() = default;

		std::string _print;
	protected:
	private:
};

#endif /* !TIMEREVENT_HPP_ */
