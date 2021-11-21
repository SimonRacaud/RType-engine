/*
** EPITECH PROJECT, 2021
** AudioEventManager
** File description:
** AudioEventManager.cpp
*/

#include "GameCore/GameCore.hpp"
#include "AudioEventManager.hpp"
#include "AudioManager/SoundManager/SoundManager.hpp"
#include "AudioManager/MusicManager/MusicManager.hpp"
#include "EngineCore.hpp"

AudioEventManager::AudioEventManager()
{
    Engine::Event::EventCallbackRegister &reg = Engine::EngineFactory::getInstance().getEventRegister();
    reg.registerCallback<AudioEventLoad>([this] (const Engine::Event::IEvent *e) {
        this->loadAudio(static_cast<const AudioEventLoad *>(e));
    });
    reg.registerCallback<AudioEventPlay>([this] (const Engine::Event::IEvent *e) {
        this->playAudio(static_cast<const AudioEventPlay *>(e));
    });
    reg.registerCallback<AudioEventStop>([this] (const Engine::Event::IEvent *e) {
        this->stopAudio(static_cast<const AudioEventStop *>(e));
    });
    reg.registerCallback<AudioEventStopAll>([this] (const Engine::Event::IEvent *e) {
        this->stopAudio(static_cast<const AudioEventStopAll *>(e));
    });
    reg.registerCallback<AudioEventPause>([this] (const Engine::Event::IEvent *e) {
        this->pauseAudio(static_cast<const AudioEventPause *>(e));
    });
    reg.registerCallback<AudioEventVolume>([this] (const Engine::Event::IEvent *e) {
        this->volumeAudio(static_cast<const AudioEventVolume *>(e));
    });
    AudioEventManager::initEvent();
}

void AudioEventManager::loadAudio(const AudioEventLoad *e)
{
    try {
        this->_list.at(e->_path);
    } catch (...) {
        switch (e->_type)
        {
            case AudioEventLoad::audioType_e::SOUND: this->_list[e->_path] = std::make_unique<SoundManager>(); break;
            case AudioEventLoad::audioType_e::MUSIC: this->_list[e->_path] = std::make_unique<MusicManager>(); break;
            default: throw std::invalid_argument("Invalid enum audioType_e"); break;
        }
        this->_list[e->_path]->setAudio(e->_path);
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

void AudioEventManager::stopAudio(const AudioEventStopAll *e)
{
    for (auto &it : this->_list) {
        try {
            it.second->stop();
        } catch (...) {
        }
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

void AudioEventManager::initEvent()
{
    int default_volume = GameCore::config->getVar<int>("DEFAULT_VOLUME");
    std::vector<std::string> sound(GameCore::config->getVectorOf<std::string>("SOUND_BULLET"));

    if (sound.size() != 2)
        throw std::invalid_argument("Need 2 sounds");
    for (auto &it : sound) {
        GET_EVENT_REG.registerEvent<AudioEventLoad>(AudioEventLoad::audioType_e::SOUND, it);
        GET_EVENT_REG.registerEvent<AudioEventVolume>(it, default_volume);
    }

    std::string exp = GameCore::config->getVar<std::string>("SOUND_EXPLOSION");
    GET_EVENT_REG.registerEvent<AudioEventLoad>(AudioEventLoad::audioType_e::SOUND, exp);
    GET_EVENT_REG.registerEvent<AudioEventVolume>(exp, default_volume);
}