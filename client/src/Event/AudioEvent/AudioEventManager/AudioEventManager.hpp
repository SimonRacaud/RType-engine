/*
** EPITECH PROJECT, 2021
** AudioEventManager
** File description:
** AudioEventManager.hpp
*/

#ifndef AUDIOEVENTMANAGER_HPP
#define AUDIOEVENTMANAGER_HPP

#include "" // TODO INCLUDE FOR REG
#include "Event/AudioEvent/AudioEventLoad.hpp"
#include "Event/AudioEvent/AudioEventPlay.hpp"
#include "Event/AudioEvent/AudioEventStop.hpp"
#include "Event/AudioEvent/AudioEventPause.hpp"
#include "Event/AudioEvent/AudioEventVolume.hpp"
#include <unordered_map>

class AudioEventManager
{
	public:
        AudioEventManager();
        ~AudioEventManager() = default;

	private:
        static void loadAudio(const AudioEventLoad *e);
        static void playAudio(const AudioEventPlay *e);
        static void stopAudio(const AudioEventStop *e);
        static void pauseAudio(const AudioEventPause *e);
        static void volumeAudio(const AudioEventVolume *e);

    private:
        std::unordered_map<std::string, std::unique_ptr<IAudioManager>> _list;
};

#endif