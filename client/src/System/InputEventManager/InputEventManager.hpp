/*
** EPITECH PROJECT, 2021
** InputEventManager
** File description:
** InputEventManager.hpp
*/

#ifndef INPUTEVENTMANAGER_HPP
#define INPUTEVENTMANAGER_HPP

#include "AInputEventManager.hpp"

class InputEventManager : AInputEventManager
{
    public:
        InputEventManager(renderToolSfml &);
        ~InputEventManager();

        void run();

    private:
        renderToolSfml &_window;
};

#endif