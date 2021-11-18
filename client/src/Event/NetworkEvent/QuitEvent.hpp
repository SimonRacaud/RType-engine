/*
** EPITECH PROJECT, 2021
** QuitEvent
** File description:
** QuitEvent.hpp
*/

#ifndef QUITEVENT_HPP
#define QUITEVENT_HPP

#include "Event/IEvent.hpp"

class QuitEvent : public Engine::Event::IEvent
{
	public:
		QuitEvent()
        {
        }
		~QuitEvent() = default;

		std::type_index getType() const override {
			return std::type_index(typeid(this));
		}
};

#endif