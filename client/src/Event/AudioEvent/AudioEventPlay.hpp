/*
** EPITECH PROJECT, 2021
** AudioEventPlay
** File description:
** AudioEventPlay.hpp
*/

#ifndef AUDIOEVENTPLAY_HPP
#define AUDIOEVENTPLAY_HPP

#include "IEvent.hpp"
#include <string>

class AudioEventPlay : public Engine::Event::IEvent
{
	public:
		AudioEventPlay(const std::string &path) : _path(path)
        {
        }
		~AudioEventPlay() = default;

		std::type_index getType() const override {
			return std::type_index(typeid(this));
		}

    public:
        std::string _path;
};

#endif