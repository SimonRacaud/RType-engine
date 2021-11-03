/*
** PERSONAL PROJECT, 2021
** EventManager
** File description:
** EventManager.hpp
*/

#ifndef EVENTMANAGER_HPP
#define EVENTMANAGER_HPP

#include <vector>
#include <memory>
#include <unordered_map>
#include <SFML/Graphics.hpp>
#include "Interface/IEventManager.hpp"

class EventManager: public IEventManager
{
    public:
        EventManager();
        EventManager(const EventManager &);
        ~EventManager();

        void refresh();
        bool isKeyPressed(const IEventManager::keyEvent_e &) const;
        vector2D getMousePos() const;
        bool mouseIsOn(const surface &) const;
        bool mouseIsOnClick(const surface &, const IEventManager::keyEvent_e &) const;

    private:
        void fetchEvent();
        bool isValideEnum(const IEventManager::keyEvent_e &) const;

        void mouseFetch(const sf::Event &);
        void mouseKeyFetch(const sf::Event &);
        void keyboardFetch(const sf::Event &);

    private:
        vector2D _mouse;
        std::vector<IEventManager::keyEvent_e> _keyStack;
        const std::unordered_map<sf::Keyboard::Key, IEventManager::keyEvent_e> _keyLink = {
            {sf::Keyboard::Up, IEventManager::keyEvent_e::KEY_UP},
            {sf::Keyboard::Down, IEventManager::keyEvent_e::KEY_DOWN},
            {sf::Keyboard::Left, IEventManager::keyEvent_e::KEY_LEFT},
            {sf::Keyboard::Right, IEventManager::keyEvent_e::KEY_RIGHT},
        };
        const std::unordered_map<sf::Mouse::Button, IEventManager::keyEvent_e> _mouseLink = {
            {sf::Mouse::Left, IEventManager::keyEvent_e::MOUSE_CLICK_LEFT},
            {sf::Mouse::Right, IEventManager::keyEvent_e::MOUSE_CLICK_RIGHT},
            {sf::Mouse::Middle, IEventManager::keyEvent_e::MOUSE_CLICK_MIDDLE},
        };
};

#endif