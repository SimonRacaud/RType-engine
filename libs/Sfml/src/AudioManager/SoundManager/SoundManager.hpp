/*
** PERSONAL PROJECT, 2021
** SoundManager
** File description:
** SoundManager.hpp
*/

#ifndef SOUNDMANAGER_HPP
#define SOUNDMANAGER_HPP

#include <memory>
#include <SFML/Audio.hpp>
#include <iostream>
#include "Interface/IAudioManager.hpp"

class SoundManager: public IAudioManager
{
    public:
        SoundManager();
        SoundManager(const SoundManager &);
        ~SoundManager();
        void play();
        void stop();
        void pause();
        void restart();
        size_t getVolume();
        void setVolume(size_t);
        void setAudio(const std::string &);

    private:
        void loadAudio(const std::string &);

    private:
        std::shared_ptr<sf::SoundBuffer> _manager;
        std::shared_ptr<sf::Sound> _sound;
        std::string _path;
        size_t _volume;
        bool _pause;
};

#endif