/*
** EPITECH PROJECT, 2021
** AudioEventManager
** File description:
** AudioEventManager.hpp
*/

#ifndef AUDIOEVENTMANAGER_HPP
#define AUDIOEVENTMANAGER_HPP

#include "Event/AudioEvent/AudioEventLoad.hpp"
#include "Event/AudioEvent/AudioEventPlay.hpp"
#include "Event/AudioEvent/AudioEventStop.hpp"
#include "Event/AudioEvent/AudioEventPause.hpp"
#include "Event/AudioEvent/AudioEventVolume.hpp"
#include "Event/EventCallBackRegister/EventCallbackRegister.hpp"
#include <unordered_map>

extern Engine::Event::EventCallbackRegister *reg;

class AudioEventManager
{
	public:
        AudioEventManager();
        ~AudioEventManager() = default;

    private:
        void loadAudio(const AudioEventLoad *e);
        void playAudio(const AudioEventPlay *e);
        void stopAudio(const AudioEventStop *e);
        void pauseAudio(const AudioEventPause *e);
        void volumeAudio(const AudioEventVolume *e);

    private:
        std::unordered_map<std::string, std::unique_ptr<IAudioManager>> _list;
};

#endif