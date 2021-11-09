/*
** EPITECH PROJECT, 2021
** AudioEventStop
** File description:
** AudioEventStop.hpp
*/

#ifndef AUDIOEVENTSTOP_HPP
#define AUDIOEVENTSTOP_HPP

#include "IEvent.hpp"
#include <string>

class AudioEventStop : public Engine::Event::IEvent
{
	public:
		AudioEventStop(const std::string &path) : _path(path)
        {
        }
		~AudioEventStop() = default;

		std::type_index getType() const override {
			return std::type_index(typeid(this));
		}

    public:
        std::string _path;
};

#endif