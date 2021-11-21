/*
** EPITECH PROJECT, 2021
** AudioEventStopAll
** File description:
** AudioEventStopAll.hpp
*/

#ifndef AUDIOEVENTSTOPALL_HPP
#define AUDIOEVENTSTOPALL_HPP

#include "Event/IEvent.hpp"
#include <string>

class AudioEventStopAll : public Engine::Event::IEvent
{
	public:
		AudioEventStopAll()
        {
        }
		~AudioEventStopAll() = default;

		std::type_index getType() const override {
			return std::type_index(typeid(this));
		}
};

#endif