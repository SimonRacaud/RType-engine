/*
** EPITECH PROJECT, 2021
** AudioEventLoad
** File description:
** AudioEventLoad.hpp
*/

#ifndef AUDIOEVENTLOAD_HPP
#define AUDIOEVENTLOAD_HPP

#include "IEvent.hpp"
#include "Interface/IAudioManager.hpp"
#include "AudioManager/SoundManager/SoundManager.hpp"
#include "AudioManager/MusicManager/MusicManager.hpp"
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
		AudioEventLoad(const audioType_e &type, const std::string &path) : _member(nullptr), _path(path)
        {
            switch (type)
            {
                case audioType_e::SOUND: this->_member = std::make_unique<SoundManager>(); break;
                case audioType_e::MUSIC: this->_member = std::make_unique<MusicManager>(); break;
                default: throw std::invalid_argument("Invalid enum audioType_e"); break;
            }
        }
		~AudioEventLoad() = default;

		std::type_index getType() const override {
			return std::type_index(typeid(this));
		}

    public:
        std::unique_ptr<IAudioManager> _member;
        std::string _path;
};

#endif