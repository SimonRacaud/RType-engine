/*
** EPITECH PROJECT, 2021
** Button
** File description:
** Button.hpp
*/

#ifndef BUTTON_HPP
#define BUTTON_HPP

#include <string>
#include <memory>
#include "Item/surface.hpp"
#include "Item/vector2f.hpp"
#include "Event/IEvent.hpp"

class Button
{
    public:
        Button(
            const std::string &text,
            const vector2D &position,
            const vector2f &scale,
            std::shared_ptr<Engine::Event::IEvent> event,
            const std::string &none = "asset/gui/button_pressed.png",
            const std::string &isOn = "asset/gui/button_over.png",
            const std::string &isClick = "asset/gui/button.png"
        );
        ~Button() = default;
};

#endif