/*
** PERSONAL PROJECT, 2021
** IEventManager
** File description:
** IEventManager.hpp
*/

#ifndef IEVENTMANAGER_HPP
#define IEVENTMANAGER_HPP

#include <string>
#include "Item/vector2D.hpp"
#include "Item/surface.hpp"

class IEventManager
{
    public:
        enum class keyEvent_e {
            KEY_EVENT_GAME,
            KEY_UP,
            KEY_DOWN,
            KEY_LEFT,
            KEY_RIGHT,
            KEY_SPACE,
            MOUSE_EVENT_GAME,
            MOUSE_CLICK_LEFT,
            MOUSE_CLICK_RIGHT,
            MOUSE_CLICK_MIDDLE,
            MAX_VALUE,
        };
        virtual ~IEventManager() = default;
        // GLOBAL
        virtual void refresh() = 0;

        // KEY
        virtual bool isKeyPressed(const keyEvent_e &) const = 0;
        virtual bool isKeyReleased(const keyEvent_e &) const = 0;
        virtual bool isStateChange(const keyEvent_e &) const = 0;

        // MOUSE
        virtual vector2D getMousePos() const = 0;
        virtual bool mouseIsOn(const surface &) const = 0;
        virtual bool mouseIsOnClick(const surface &, const keyEvent_e &) const = 0;
};

#endif