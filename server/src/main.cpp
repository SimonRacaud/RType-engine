/*
** EPITECH PROJECT , 2021
** main
** File description:
** simon
*/

#include "ServerCore/ServerCore.hpp"

int main(void)
{
    try {
        ServerCore core;

        core.run();
    } catch (const std::exception &e) {
        std::cerr << "ERROR: Invalid exit status -> " << e.what() << std::endl;
    } catch (...) {
        std::cerr << "ERROR: Invalid exit status" << std::endl;
    }
}