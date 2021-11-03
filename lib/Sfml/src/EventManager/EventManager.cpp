/*
** PERSONAL PROJECT, 2021
** EventManager
** File description:
** EventManager.cpp
*/

#include <algorithm>
#include "EventManager/EventManager.hpp"

EventManager::EventManager(): _mouse(), _keyStack()
{
}

EventManager::EventManager(const EventManager &src): _mouse(src._mouse), _keyStack(src._keyStack)
{
}

EventManager::~EventManager()
{
    this->_keyStack.clear();
}

void EventManager::refresh()
{
    this->_keyStack.clear();
    this->fetchEvent();
}

bool EventManager::isKeyPressed(const IEventManager::keyEvent_e &key) const
{
    if (!this->isValideEnum(key))
        throw std::invalid_argument("Invalid key type");

    auto pos = std::find(this->_keyStack.begin(), this->_keyStack.end(), key);

    return pos != this->_keyStack.end();
}

vector2D EventManager::getMousePos() const
{
    return this->_mouse;
}

bool EventManager::mouseIsOn(const surface &selected) const
{
    bool x = this->_mouse.x > selected.pos.x && this->_mouse.x < selected.pos.x + selected.size.x;
    bool y = this->_mouse.y > selected.pos.y && this->_mouse.y < selected.pos.y + selected.size.y;

    return x && y;
}

bool EventManager::mouseIsOnClick(const surface &selected, const IEventManager::keyEvent_e &key) const
{
    bool click = this->isKeyPressed(key);
    bool on = this->mouseIsOn(selected);

    return on && click;
}

bool EventManager::isValideEnum(const IEventManager::keyEvent_e &key) const
{
    bool active = key != IEventManager::keyEvent_e::MAX_VALUE && key != IEventManager::keyEvent_e::MOUSE_EVENT && key != IEventManager::keyEvent_e::KEY_EVENT;
    bool invalid = key < static_cast<IEventManager::keyEvent_e>(0) || key >= IEventManager::keyEvent_e::MAX_VALUE;

    return active && !invalid;
}

void EventManager::fetchEvent()
{
    std::shared_ptr<sf::Window> window = nullptr; // TODO TAKE DECISION
    sf::Event event;
    
    while (window->pollEvent(event)) {
        switch (event.type)
        {
            case sf::Event::Event::Closed: window->close(); break;
            case sf::Event::MouseMoved: this->mouseFetch(event); break;
            case sf::Event::EventType::KeyPressed: this->keyboardFetch(event); break;
            case sf::Event::EventType::MouseButtonPressed: this->mouseKeyFetch(event); break;
            default: break;
        }
    }
}

void EventManager::mouseFetch(const sf::Event &event)
{
    this->_mouse = vector2D(event.mouseMove.x, event.mouseMove.y);
}

void EventManager::mouseKeyFetch(const sf::Event &event)
{
    try {
        this->_keyStack.push_back(this->_mouseLink.at(event.mouseButton.button));
    } catch(...) {
    }
}

void EventManager::keyboardFetch(const sf::Event &event)
{
    try {
        this->_keyStack.push_back(this->_keyLink.at(event.key.code));
    } catch(...) {
    }
}