/*
** EPITECH PROJECT, 2021
** RType
** File description:
** MultipleEvent
*/

#ifndef MULTIPLEEVENT_HPP_
#define MULTIPLEEVENT_HPP_

#include "IEvent.hpp"
#include <string>


class MultipleEvent : public Engine::Event::IEvent {
	public:
		MultipleEvent(int nb) : _nb(nb) {}
		~MultipleEvent() = default;

		std::type_index getType() const override {
			return std::type_index(typeid(this));
		}
		int _nb;
	protected:
	private:
};

struct OtherEvent : public Engine::Event::IEvent {
	int _other;

	OtherEvent(int nb) : _other(nb) {}
};

#endif /* !MULTIPLEEVENT_HPP_ */
