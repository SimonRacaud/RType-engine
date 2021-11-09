/*
** PERSONAL PROJECT, 2021
** SoundManager
** File description:
** SoundManager.cpp
*/

#include "SoundManager.hpp"

SoundManager::SoundManager(): _manager(nullptr), _sound(nullptr), _path(""), _volume(100), _pause(false)
{
}

SoundManager::SoundManager(const SoundManager &src): _manager(src._manager), _sound(src._sound), _path(src._path), _volume(src._volume), _pause(false)
{
}

SoundManager::~SoundManager()
{
    if (this->_manager)
        this->_manager.reset();
    if (this->_sound) {
        this->_sound->stop();
        this->_sound.reset();
    }
}

void SoundManager::play()
{
    if (!this->_manager)
        this->_manager = std::make_shared<sf::SoundBuffer>();
    if (!this->_sound)
        this->_sound = std::make_shared<sf::Sound>();
    this->loadAudio(this->_path);
    this->_sound->play();
}

void SoundManager::stop()
{
    if (!this->_manager)
        throw std::invalid_argument("Audio must be play");
    this->_sound->stop();
}

void SoundManager::pause()
{
    if (!this->_manager || !this->_sound)
        throw std::invalid_argument("Audio must be play");
    if (this->_pause) {
        this->_sound->pause();
    } else {
        this->_sound->play();
    }
    this->_pause = !this->_pause;
}

void SoundManager::restart()
{
    if (!this->_manager || !this->_sound)
        throw std::invalid_argument("Audio must be play");
    this->_sound->stop();
    this->_sound->play();
}

size_t SoundManager::getVolume()
{
    return this->_volume;
}

void SoundManager::setVolume(size_t newVolume)
{
    if (this->_sound)
        this->_sound->setVolume(this->_volume);
    this->_volume = newVolume;
}

void SoundManager::setAudio(const std::string &name)
{
    if (this->_manager && this->_sound)
        this->loadAudio(name);
    this->_path = name;
}

void SoundManager::loadAudio(const std::string &name)
{
    if (!this->_manager->loadFromFile(name))
        throw std::invalid_argument("Failed to open: " + name);
    this->_sound->setBuffer(*(this->_manager.get()));
}