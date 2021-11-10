/*
** EPITECH PROJECT , 2021
** display_components
** File description:
** \file display_components.cpp
** \author simon
** \brief
** \date 08/11/2021
*/

#include "display.hpp"

using namespace Engine;
using namespace std;

ostream& operator<<(ostream& os, const Position& comp)
{
    return os << "[Position: x=" << comp.x << ", y=" << comp.y << "]";
}

ostream& operator<<(ostream& os, const Velocity& comp)
{
    return os << "[Velocity: x=" << comp.x << ", y=" << comp.y << "]";
}