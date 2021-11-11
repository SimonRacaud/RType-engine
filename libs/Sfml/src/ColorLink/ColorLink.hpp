/*
** PERSONAL PROJECT, 2021
** ColorLink
** File description:
** ColorLink.hpp
*/

#ifndef COLORLINK_HPP
#define COLORLINK_HPP

#include "color.hpp"
#include "build.hpp"
#include <unordered_map>

class ColorLink
{
    public:
        static sf::Color getColor(color_e);
};

#endif