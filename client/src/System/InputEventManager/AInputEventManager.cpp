/*
** EPITECH PROJECT, 2021
** AInputEventManager
** File description:
** AInputEventManager.cpp
*/

#include "AInputEventManager.hpp"

AInputEventManager::AInputEventManager() : _event(std::make_unique<EventManager>())
{
}

AInputEventManager::~AInputEventManager()
{
    this->_event.reset();
}

bool AInputEventManager::isKeyPressed(const Event::keyEvent_e &key) const
{
    return this->_event->isKeyPressed(key);
}

vector2D AInputEventManager::getMousePos() const
{
    return this->_event->getMousePos();
}

bool AInputEventManager::mouseIsOn(const surface &where) const
{
    return this->_event->mouseIsOn(where);
}

bool AInputEventManager::mouseIsOnClick(const surface &where, const Event::keyEvent_e &key) const
{
    return this->_event->mouseIsOnClick(where, key);
}

void AInputEventManager::refresh(renderToolSfml &window)
{
    this->_event->refresh(window);
}