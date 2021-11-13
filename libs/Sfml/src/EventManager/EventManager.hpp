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
#include "build.hpp"
#include "Interface/IEventManager.hpp"

class EventManager: public IEventManager<renderToolSfml>
{
    public:
        EventManager();
        EventManager(const EventManager &);
        ~EventManager();

        void refresh(renderToolSfml &);
        bool isKeyPressed(const IEventManager<renderToolSfml>::keyEvent_e &) const;
        vector2D getMousePos() const;
        bool mouseIsOn(const surface &) const;
        bool mouseIsOnClick(const surface &, const IEventManager<renderToolSfml>::keyEvent_e &) const;

    private:
        void fetchEvent(renderToolSfml &);
        bool isValideEnum(const IEventManager<renderToolSfml>::keyEvent_e &) const;

        void mouseFetch(const sf::Event &);
        void mouseKeyFetch(const sf::Event &);
        void keyboardFetch(const sf::Event &);

    private:
        vector2D _mouse;
        std::vector<IEventManager<renderToolSfml>::keyEvent_e> _keyStack;
        const std::unordered_map<sf::Keyboard::Key, IEventManager<renderToolSfml>::keyEvent_e> _keyLink = {
            {sf::Keyboard::Up, IEventManager<renderToolSfml>::keyEvent_e::KEY_UP},
            {sf::Keyboard::Down, IEventManager<renderToolSfml>::keyEvent_e::KEY_DOWN},
            {sf::Keyboard::Left, IEventManager<renderToolSfml>::keyEvent_e::KEY_LEFT},
            {sf::Keyboard::Right, IEventManager<renderToolSfml>::keyEvent_e::KEY_RIGHT},
            {sf::Keyboard::Space, IEventManager<renderToolSfml>::keyEvent_e::KEY_SPACE}
        };
        const std::unordered_map<sf::Mouse::Button, IEventManager<renderToolSfml>::keyEvent_e> _mouseLink = {
            {sf::Mouse::Left, IEventManager<renderToolSfml>::keyEvent_e::MOUSE_CLICK_LEFT},
            {sf::Mouse::Right, IEventManager<renderToolSfml>::keyEvent_e::MOUSE_CLICK_RIGHT},
            {sf::Mouse::Middle, IEventManager<renderToolSfml>::keyEvent_e::MOUSE_CLICK_MIDDLE},
        };
};

#endif