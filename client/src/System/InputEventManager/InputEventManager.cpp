/*
** EPITECH PROJECT, 2021
** InputEventManager
** File description:
** InputEventManager.cpp
*/

#include "InputEventManager.hpp"

InputEventManager::InputEventManager(renderToolSfml &window) : AInputEventManager(), _window(window)
{
}

InputEventManager::~InputEventManager()
{
}

void InputEventManager::run()
{
    // START

    // TODO FILL

    // END
    this->refresh(this->_window);
}