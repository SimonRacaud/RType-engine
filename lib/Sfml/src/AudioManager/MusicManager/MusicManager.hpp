/*
** PERSONAL PROJECT, 2021
** MusicManager
** File description:
** MusicManager.hpp
*/

#ifndef MUSICMANAGER_HPP
#define MUSICMANAGER_HPP

#include <memory>
#include <SFML/Audio.hpp>
#include <iostream>
#include "Interface/IAudioManager.hpp"

class MusicManager
{
    public:
        MusicManager();
        MusicManager(const MusicManager &);
        ~MusicManager();
        void play();
        void pause();
        void restart();
        size_t getVolume();
        void setVolume(size_t);
        void setAudio(const std::string &);

    private:
        void loadAudio(const std::string &);

    private:
        std::shared_ptr<sf::Music> _manager;
        std::string _path;
        size_t _volume;
        bool _pause;
};

#endif