/*
** EPITECH PROJECT , 2021
** main
** File description:
** simon
*/

#include "GameCore/GameCore.hpp"
#include <stdexcept>

int main(void)
{
    try {
        GameCore core;

        core.run();
    } catch (const std::exception &e) {
        std::cout << "ERROR: Invalid exit status : " << e.what() << std::endl;
    } catch (...) {
        std::cout << "ERROR: Invalid exit status" << std::endl;
    }
    return EXIT_SUCCESS;
}