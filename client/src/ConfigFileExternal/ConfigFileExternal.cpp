/*
** EPITECH PROJECT, 2021
** ConfigFileExternal
** File description:
** ConfigFileExternal.cpp
*/

#include "Item/vector2D.hpp"
#include "ConfigFileExternal.hpp"

std::any ConfigFileExternal::getVector2D(const std::string &data)
{
    vector2D value;

    if (!ConfigFileTools::matchWithRegex("^\\{.*\\}$", data))
        throw std::invalid_argument("Incorrect line format for vector2D: " + data);
    try {
        ConfigFile toRead(ConfigFileTools::getSplittedObj(data));

        value.x = toRead.getVar<int>("X");
        value.y = toRead.getVar<int>("Y");
    } catch ([[maybe_unused]] const std::out_of_range &e) {
        throw std::invalid_argument("Invalide vector2D: " + data);
    }
    return std::any(std::in_place_type<vector2D>, value);
}