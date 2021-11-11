/*
** PERSONAL PROJECT, 2021
** ConfigFileTools
** File description:
** ConfigFileTools.hpp
*/

#ifndef CONFIGFILETOOLS_HPP
#define CONFIGFILETOOLS_HPP

#include <any>
#include <iostream>

class ConfigFileTools {
  public:
    // LOADER
    [[nodiscard]] static std::any getInt(const std::string &data);
    [[nodiscard]] static std::any getBool(const std::string &data);
    [[nodiscard]] static std::any getFloat(const std::string &data);
    [[nodiscard]] static std::any getDouble(const std::string &data);
    [[nodiscard]] static std::any getString(const std::string &data);

    // TOOLS
    [[nodiscard]] static bool insensitiveCmp(const std::string &a, const std::string &b);
    [[nodiscard]] static bool matchWithRegex(const std::string &regex, const std::string &line);
    [[nodiscard]] static std::string getAfterToken(const std::string &line, const std::string &match);
    [[nodiscard]] static std::vector<std::string> getSplittedObj(const std::string &line);
  
  private:
    [[nodiscard]] static size_t getFirstOf(const std::string &line, char toFound);
};

#endif