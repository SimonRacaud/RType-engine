/*
** PERSONAL PROJECT, 2021
** IAudioManager
** File description:
** IAudioManager.hpp
*/

#ifndef IAUDIOMANAGER_HPP
#define IAUDIOMANAGER_HPP

#include <string>

class IAudioManager
{
    public:
        virtual ~IAudioManager() = default;
        virtual void play() = 0;
        virtual void stop() = 0;
        virtual void pause() = 0;
        virtual void restart() = 0;
        virtual size_t getVolume() = 0;
        virtual void setVolume(size_t) = 0;
        virtual void setAudio(const std::string &) = 0;
};

#endif