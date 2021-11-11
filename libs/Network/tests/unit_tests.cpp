/*
** EPITECH PROJECT, 2019
** unit tests with criterion
** File description:
** just triing
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <iostream>
#include "test.hpp"

static const char my_timeout = 2;

Test(my_function, my_function_description, .timeout = my_timeout, .disabled = MY_DISABLEMENT)
{
    OSRedirector oss(std::cout);

    my_function();
    cr_assert_eq(oss.getContent(), "output test\n");
}

Test(my_other_fct, my_function_description, .timeout = my_timeout, .disabled = MY_DISABLEMENT)
{
    cr_assert(my_other_fct == 10101);
}