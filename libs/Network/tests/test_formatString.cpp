/*
** EPITECH PROJECT, 2019
** unit tests with criterion
** File description:
** just triing
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <iostream>
#include <string>

#include "test.hpp"
#include "formatString.hpp"

static const char my_timeout = 2;

Test(formatConnection, noString, .timeout = my_timeout, .disabled = MY_DISABLEMENT)
{
    const std::string expected{""};
    const std::string result{formatString::format("", "0.0", 234)};

    cr_assert_eq(expected, result);
}

Test(formatConnection, noFormat, .timeout = my_timeout, .disabled = MY_DISABLEMENT)
{
    const std::string expected{"hello"};
    const std::string result{formatString::format("hello", "0.0", 234)};

    cr_assert_eq(expected, result);
}

Test(formatConnection, ipFormat, .timeout = my_timeout, .disabled = MY_DISABLEMENT)
{
    const std::string expected{"hello 0.0"};
    const std::string result{formatString::format("hello {}", "0.0")};

    cr_assert_eq(expected, result);
}

Test(formatConnection, portFormat, .timeout = my_timeout, .disabled = MY_DISABLEMENT)
{
    const std::string expected{"hello 234"};
    const std::string result{formatString::format("hello {}", 234)};

    cr_assert_eq(expected, result);
}

Test(formatConnection, ipPortFormat, .timeout = my_timeout, .disabled = MY_DISABLEMENT)
{
    const std::string expected{"hello 111.111.111.111, 2342"};
    const std::string result{formatString::format("hello {}, {}", "111.111.111.111", 2342)};

    cr_assert_eq(expected, result);
}