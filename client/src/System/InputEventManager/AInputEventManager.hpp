/*
** EPITECH PROJECT, 2021
** AInputEventManager
** File description:
** AInputEventManager.hpp
*/

#ifndef AINPUTEVENTMANAGER_HPP
#define AINPUTEVENTMANAGER_HPP

#include <memory>
#include "build.hpp"
#include "graphical.hpp"

class AInputEventManager
{
    using Event = IEventManager<renderToolSfml>;
    public:
        AInputEventManager();
        ~AInputEventManager();

        virtual void run() = 0;

        bool isKeyPressed(const Event::keyEvent_e &) const;
        vector2D getMousePos() const;
        bool mouseIsOn(const surface &) const;
        bool mouseIsOnClick(const surface &, const Event::keyEvent_e &) const;

    protected:
        void refresh(renderToolSfml &);
    private:
        std::unique_ptr<Event> _event;
};

#endif