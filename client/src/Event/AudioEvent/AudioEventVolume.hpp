/*
** EPITECH PROJECT, 2021
** AudioEventVolume
** File description:
** AudioEventVolume.hpp
*/

#ifndef AUDIOEVENTVOLUME_HPP
#define AUDIOEVENTVOLUME_HPP

#include "Event/IEvent.hpp"
#include <string>

class AudioEventVolume : public Engine::Event::IEvent
{
	public:
		AudioEventVolume(const std::string &path, size_t volume) : _path(path), _volume(volume)
        {
        }
		~AudioEventVolume() = default;

		std::type_index getType() const override {
			return std::type_index(typeid(this));
		}

    public:
        std::string _path;
        size_t _volume;
};

#endif