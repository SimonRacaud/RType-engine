/*
** EPITECH PROJECT , 2021
** display_components
** File description:
** \file display_components.hpp
** \author simon
** \brief
** \date 08/11/2021
*/

#ifndef DISPLAY_HPP
#define DISPLAY_HPP

#include <iostream>
#include "Components/Position.hpp"
#include "Components/Velocity.hpp"

std::ostream& operator<<(std::ostream& os, const Engine::Velocity& comp);

std::ostream& operator<<(std::ostream& os, const Engine::Velocity& comp);

#endif // DISPLAY_HPP
