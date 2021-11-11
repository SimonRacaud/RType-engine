/*
** EPITECH PROJECT , 2021
** main
** File description:
** simon
*/

#include "GameCore/GameCore.hpp"

int main(void)
{
    try {
        GameCore core;

        core.run();
    } catch (...) {
        std::cout << "ERROR: Invalid exit status" << std::endl;
    }
    return EXIT_SUCCESS;
}