/*
** EPITECH PROJECT, 2021
** RType
** File description:
** PrintHelloEvent
*/

#ifndef PRINTHELLOEVENT_HPP_
#define PRINTHELLOEVENT_HPP_

#include "IEvent.hpp"
#include <string>

class PrintEvent : public Engine::Event::IEvent {
	public:
		PrintEvent(const std::string &toPrint) : _toPrint(toPrint) {}
		~PrintEvent() = default;

		std::type_index getType() const override {
			return std::type_index(typeid(this));
		}
		std::string _toPrint;
};

#endif /* !PRINTHELLOEVENT_HPP_ */
