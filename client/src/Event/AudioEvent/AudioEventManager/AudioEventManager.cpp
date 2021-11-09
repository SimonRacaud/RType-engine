/*
** EPITECH PROJECT, 2021
** AudioEventManager
** File description:
** AudioEventManager.cpp
*/

#include "AudioEventManager.hpp"

AudioEventManager::AudioEventManager()
{
    EventRegister->registerCallback(loadAudio);
    EventRegister->registerCallback(playAudio);
    EventRegister->registerCallback(stopAudio);
    EventRegister->registerCallback(pauseAudio);
    EventRegister->registerCallback(volumeAudio);
}

void AudioEventManager::loadAudio(const AudioEventLoad *e)
{
    try {
        this->_list.at(e->_path);
        e->_member.reset();
    } catch (...) {
        e->_member->setAudio(e->_path);
        this->_list[e->_path] = std::move(e->_member);
    }
}

void AudioEventManager::playAudio(const AudioEventPlay *e)
{
    try {
        this->_list.at(e->_path)->play();
    } catch (...) {
        throw std::invalid_argument("Invalid sound to play");
    }
}

void AudioEventManager::stopAudio(const AudioEventStop *e)
{
    try {
        this->_list.at(e->_path)->stop();
    } catch (...) {
        throw std::invalid_argument("Invalid sound to stop");
    }
}

void AudioEventManager::pauseAudio(const AudioEventPause *e)
{
    try {
        this->_list.at(e->_path)->pause();
    } catch (...) {
        throw std::invalid_argument("Invalid sound to pause");
    }
}

void AudioEventManager::volumeAudio(const AudioEventVolume *e)
{
    try {
        this->_list.at(e->_path)->setVolume(e->_volume);
    } catch (...) {
        throw std::invalid_argument("Invalid sound to setVolume");
    }
}