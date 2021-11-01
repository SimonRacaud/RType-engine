/*
** PERSONAL PROJECT, 2021
** GetterName
** File description:
** GetterName.cpp
*/

#include "FactoryObject/GetterName/GetterName.hpp"

std::string GetterName::getNameAudio()
{
    static unsigned int it = 0;

    return "Audio: " + std::to_string(it++);
}

std::string GetterName::getNameSprite()
{
    static unsigned int it = 0;

    return "Sprite: " + std::to_string(it++);
}

std::string GetterName::getNameKeyEvent()
{
    static unsigned int it = 0;

    return "KeyEvent: " + std::to_string(it++);
}

std::string GetterName::getNameWindow()
{
    static unsigned int it = 0;

    return "Window: " + std::to_string(it++);
}

std::string GetterName::getNameAnimation()
{
    static unsigned int it = 0;

    return "Animation: " + std::to_string(it++);
}