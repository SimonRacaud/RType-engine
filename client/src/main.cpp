/*
** EPITECH PROJECT , 2021
** main
** File description:
** simon
*/

#include "SfmlModule.hpp"

int main(int ac, char **av)
{
    SfmlModule core;

    while (core.isOpen())
        core.play();
    return 0;
}