/*
** EPITECH PROJECT, 2021
** AudioEventPause
** File description:
** AudioEventPause.hpp
*/

#ifndef AUDIOEVENTPAUSE_HPP
#define AUDIOEVENTPAUSE_HPP

#include "Event/IEvent.hpp"
#include <string>

class AudioEventPause : public Engine::Event::IEvent
{
	public:
		AudioEventPause(const std::string &path) : _path(path)
        {
        }
		~AudioEventPause() = default;

		std::type_index getType() const override {
			return std::type_index(typeid(this));
		}

    public:
        std::string _path;
};

#endif