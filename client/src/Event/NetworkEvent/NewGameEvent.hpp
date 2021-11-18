/*
** EPITECH PROJECT, 2021
** NewGameEvent
** File description:
** NewGameEvent.hpp
*/

#ifndef NEWGAMEEVENT_HPP
#define NEWGAMEEVENT_HPP

#include "Event/IEvent.hpp"

class NewGameEvent : public Engine::Event::IEvent
{
	public:
		NewGameEvent()
        {
        }
		~NewGameEvent() = default;

		std::type_index getType() const override {
			return std::type_index(typeid(this));
		}
};

#endif