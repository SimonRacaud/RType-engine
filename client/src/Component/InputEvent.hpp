/*
** EPITECH PROJECT, 2021
** GameEngine
** File description:
** 27/05/2021 InputEvent.hpp.h
*/

#ifndef INPUTEVENT_HPP
#define INPUTEVENT_HPP

#include <functional>
#include "build.hpp"
#include "Interface/IEventManager.hpp"
#include "BaseComponent/BaseComponent.hpp"

namespace Engine
{
    struct InputEvent : public BaseComponent<InputEvent> {
        InputEvent(std::function<void (const Engine::Entity &)> func) : _func(func)
        {
            if (!func)
                throw std::invalid_argument("Invalid std::fonction -> nullptr");
        }
        InputEvent() = delete;
        virtual ~InputEvent() = default;

        std::function<void (const Engine::Entity &entity)> _func;
    };
}

#endif