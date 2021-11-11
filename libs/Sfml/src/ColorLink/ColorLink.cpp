/*
** PERSONAL PROJECT, 2021
** ColorLink
** File description:
** ColorLink.hpp
*/

#include "ColorLink.hpp"

sf::Color ColorLink::getColor(color_e color)
{
    const std::unordered_map<color_e, sf::Color> colorLink = {
        {color_e::RED, sf::Color::Red},
        {color_e::BLUE, sf::Color::Blue},
        {color_e::GREEN, sf::Color::Green},
        {color_e::BLACK, sf::Color::Black},
        {color_e::WHITE, sf::Color::White},
    };

    return colorLink.at(color);
}