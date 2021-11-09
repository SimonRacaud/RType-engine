/*
** PERSONAL PROJECT, 2021
** MusicManager
** File description:
** MusicManager.cpp
*/

#include "MusicManager.hpp"

MusicManager::MusicManager(): _manager(nullptr), _path(""), _volume(100), _pause(false)
{
}

MusicManager::MusicManager(const MusicManager &src): _manager(src._manager), _path(src._path), _volume(src._volume), _pause(false)
{
}

MusicManager::~MusicManager()
{
    if (this->_manager) {
        this->_manager->stop();
        this->_manager.reset();
    }
}

void MusicManager::play()
{
    if (!this->_manager) {
        this->_manager = std::make_shared<sf::Music>();
        this->loadAudio(this->_path);
        this->_manager->setVolume(this->_volume);
    }
    this->_manager->play();
}

void MusicManager::stop()
{
    if (!this->_manager)
        throw std::invalid_argument("Audio must be play");
    this->_manager->stop();
}

void MusicManager::pause()
{
    if (!this->_manager)
        throw std::invalid_argument("Audio must be play");
    if (this->_pause) {
        this->_manager->pause();
    } else {
        this->_manager->play();
    }
    this->_pause = !this->_pause;
}

void MusicManager::restart()
{
    if (!this->_manager)
        throw std::invalid_argument("Audio must be play");
    this->_manager->stop();
    this->_manager->play();
}

size_t MusicManager::getVolume()
{
    return this->_volume;
}

void MusicManager::setVolume(size_t newVolume)
{
    if (this->_manager)
        this->_manager->setVolume(this->_volume);
    this->_volume = newVolume;
}

void MusicManager::setAudio(const std::string &name)
{
    if (this->_manager) {
        this->_manager->stop();
        this->loadAudio(name);
    }
    this->_path = name;
}

void MusicManager::loadAudio(const std::string &name)
{
    if (!this->_manager->openFromFile(name))
        throw std::invalid_argument("Failed to open: " + name);
    this->_manager->setLoop(true);
}