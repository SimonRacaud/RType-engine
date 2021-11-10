/*
** EPITECH PROJECT, 2021
** RType
** File description:
** TimerEvent
*/

#ifndef TIMEREVENT_HPP_
#define TIMEREVENT_HPP_

#include "Event/IEvent.hpp"
#include <string>

class TimerEvent : public Engine::Event::IEvent {
	public:
		TimerEvent(const std::string &print) : _print(print) {}
		~TimerEvent() = default;

		virtual std::type_index getType() const override {
			return std::type_index(typeid(this));
		}

		std::string _print;
	protected:
	private:
};

#endif /* !TIMEREVENT_HPP_ */
