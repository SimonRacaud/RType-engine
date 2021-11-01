/*
** EPITECH PROJECT , 2021
** main
** File description:
** simon
*/

#include "ConfigFile.hpp"

int main(int ac, char **av)
{
    if (ac != 2)
        return 84;
    ConfigFile conf(av[1]);

    std::cout << conf.getVar<int>("exampleInt") << std::endl;
    std::cout << conf.getVar<float>("exampleFloat") << std::endl;
    std::cout << conf.getVar<std::string>("exampleString") << std::endl;
    std::cout << (conf.getVar<bool>("exampleBool") ? "true" : "false") << std::endl;
    return 0;
}