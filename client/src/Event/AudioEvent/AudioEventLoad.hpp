/*
** EPITECH PROJECT, 2021
** AudioEventLoad
** File description:
** AudioEventLoad.hpp
*/

#ifndef AUDIOEVENTLOAD_HPP
#define AUDIOEVENTLOAD_HPP

#include "Event/IEvent.hpp"
#include "Interface/IAudioManager.hpp"
#include <memory>
#include <string>

class AudioEventLoad : public Engine::Event::IEvent
{
    public:
        enum class audioType_e
        {
            SOUND,
            MUSIC
        };

	public:
		AudioEventLoad(const audioType_e &type, const std::string &path) : _type(type), _path(path)
        {
        }
		~AudioEventLoad() = default;

		std::type_index getType() const override {
			return std::type_index(typeid(this));
		}

    public:
        audioType_e _type;
        std::string _path;
};

#endif