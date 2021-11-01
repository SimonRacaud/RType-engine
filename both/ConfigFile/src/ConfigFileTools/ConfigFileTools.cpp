/*
** PERSONAL PROJECT, 2021
** ConfigFileTools
** File description:
** ConfigFileTools.cpp
*/

#include <regex>
#include <algorithm>
#include "ConfigFileTools.hpp"

/*
** LOADER
*/

std::any ConfigFileTools::getInt(const std::string &data)
{
    int value = 0;

    if (!ConfigFileTools::matchWithRegex("^(-)?\\d*$", data))
        throw std::invalid_argument("Incorrect line format for INT: " + data);
    try {
        value = std::stoi(data);
    } catch ([[maybe_unused]] const std::out_of_range &e) {
        throw std::invalid_argument("Invalide INT: " + data);
    }
    return std::any(std::in_place_type<int>, value);
}

std::any ConfigFileTools::getFloat(const std::string &data)
{
    float value = 0;

    if (!ConfigFileTools::matchWithRegex("^(-)?\\d*(.)?\\d*$", data))
        throw std::invalid_argument("Incorrect line format for FLOAT: " + data);
    try {
        value = std::stof(data);
    } catch ([[maybe_unused]] const std::out_of_range &e) {
        throw std::invalid_argument("Invalide FLOAT");
    }
    return std::any(std::in_place_type<float>, value);
}

std::any ConfigFileTools::getDouble(const std::string &data)
{
    double value = 0;

    if (!ConfigFileTools::matchWithRegex("^(-)?\\d*(.)?\\d*$", data))
        throw std::invalid_argument("Incorrect line format for DOUBLE: " + data);
    try {
        value = std::stod(data);
    } catch ([[maybe_unused]] const std::out_of_range &e) {
        throw std::invalid_argument("Invalide DOUBLE");
    }
    return std::any(std::in_place_type<double>, value);
}

std::any ConfigFileTools::getString(const std::string &data)
{
    if (!ConfigFileTools::matchWithRegex("^\".*\"$", data))
        throw std::invalid_argument("Incorrect line format for STD::STRING: " + data);
    return std::any(std::in_place_type<std::string>, data.substr(1, data.length() - 2));
}

std::any ConfigFileTools::getBool(const std::string &data)
{
    bool value = false;
    std::string booleanValue;

    if (!ConfigFileTools::matchWithRegex("^'.*'$", data))
        throw std::invalid_argument("Incorrect line format for BOOL: " + data);
    booleanValue = data.substr(1, data.length() - 2);
    if (ConfigFileTools::insensitiveCmp("true", booleanValue)) {
        value = true;
    } else if (ConfigFileTools::insensitiveCmp("false", booleanValue)) {
        value = false;
    } else {
        throw std::invalid_argument("Invalide BOOL");
    }
    return std::any(std::in_place_type<bool>, value);
}

/*
** TOOLS
*/

bool ConfigFileTools::matchWithRegex(const std::string &regex, const std::string &line)
{
    std::regex regexValue(regex);

    return std::regex_search(line, regexValue);
}

std::string ConfigFileTools::getAfterToken(const std::string &line, const std::string &match)
{
    return line.substr(line.find(match) + match.length(), line.length());
}

bool ConfigFileTools::insensitiveCmp(const std::string &a, const std::string &b)
{
    return std::equal(a.begin(), a.end(), b.begin(), b.end(),
        [](char a, char b) {
            return toupper(a) == toupper(b);
        }
    );
}