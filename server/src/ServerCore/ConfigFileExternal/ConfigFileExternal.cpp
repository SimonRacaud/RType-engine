/*
** EPITECH PROJECT, 2021
** ConfigFileExternal
** File description:
** ConfigFileExternal.cpp
*/

#include <tuple>
#include "ConfigFileExternal.hpp"

std::any ConfigFileExternal::getPairIntInt(const std::string &data)
{
    std::pair<int, int> value;

    if (!ConfigFileTools::matchWithRegex("^\\{.*\\}$", data))
        throw std::invalid_argument("Incorrect line format for std::pair<int, int>: " + data);
    try {
        ConfigFile toRead(ConfigFileTools::getSplittedObj(data));

        value.first = toRead.getVar<int>("first");
        value.second = toRead.getVar<int>("second");
    } catch ([[maybe_unused]] const std::out_of_range &e) {
        throw std::invalid_argument("Invalid std::pair<int, int>: " + data);
    }
    return std::any(std::in_place_type<std::pair<int, int>>, value);
}