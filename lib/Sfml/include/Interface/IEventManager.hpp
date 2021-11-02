/*
** PERSONAL PROJECT, 2021
** IEventManager
** File description:
** IEventManager.hpp
*/

#ifndef IEVENTMANAGER_HPP
#define IEVENTMANAGER_HPP

#include <string>

class IEventManager
{
    public:
        enum class keyEvent_e
        {
            KEY_EVENT,
            KEY_UP,
            KEY_DOWN,
            KEY_LEFT,
            KEY_RIGHT,
            MOUSE_EVENT,
            MOUSE_CLICK_LEFT,
            MOUSE_CLICK_RIGHT,
            MOUSE_CLICK_MIDDLE,
            MAX_VALUE
        };

    public:
        ~IEventManager() = default;
        // GLOBAL
        virtual void refresh() = 0;

        // KEY
        virtual bool isKeyPressed(const keyEvent_e &) const = 0;

        // MOUSE
        virtual bool mouseIsOn() const = 0; // TODO edit with surface
        virtual bool mouseIsOnClick(const keyEvent_e &) const = 0; // TODO edit with surface
        virtual void getMousePos() const = 0; // TODO edit with vector
};

#endif