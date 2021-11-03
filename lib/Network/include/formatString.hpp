/*
** EPITECH PROJECT, 2021
** formatString.hpp
** File description:
** Format string easily
*/

#ifndef MY_CPP_CANEVA_FORMATSTR_HPP
#define MY_CPP_CANEVA_FORMATSTR_HPP

#include <string>

namespace std
{
    inline std::string to_string(std::string my_str)
    {
        return my_str;
    }
} // namespace std

class formatString {
  public:
    /**
     * @brief Format a string
     * @tparam T Any type compatible with std::to_string()
     * @tparam Types Variadic number of types compatible with std::to_string()
     * @param fmt The string to format, should contain <formatIdentifier> where variables should be positionned
     * @param toPlace First variable that should be placed in the formatted string instead of <formatIdentifier>
     * @param otherToPlace Variadic number of variables that should be placed int the formatted string
     * @return The initial string, with, instead of <formatIdentifier> variables passed by parameter
     */
    // todo concept that obliges T to be compatible with std::to_string()
    template <typename T, typename... Types>
    static std::string format(std::string fmt, T toPlace, Types... otherToPlace)
    {
        if (fmt.find(formatIdentifier) != std::string::npos)
            fmt.replace(fmt.find(formatIdentifier), formatIdentifier.size(), std::to_string(toPlace));
        else
            return fmt;
        return formatString::format(fmt, otherToPlace...);
    }

    static std::string removeIdentifiers(std::string fmt)
    {
        while (fmt.find(formatIdentifier)) {
            fmt.replace(fmt.find(formatIdentifier), formatIdentifier.size(), "");
        }
        return fmt;
    }

  private:
    static std::string format(std::string fmt)
    {
        return fmt;
    }

  public:
    /**
     * @brief The string pattern that is to be replaced by variables passed to format()
     * @note Not const to let the user change
     */
    static std::string formatIdentifier;
};

inline std::string formatString::formatIdentifier = "{}";

#endif // MY_CPP_CANEVA_FORMATSTR_HPP