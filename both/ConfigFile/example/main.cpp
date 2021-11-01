/*
** EPITECH PROJECT , 2021
** main
** File description:
** simon
*/

#include "ConfigFile.hpp"
#include "ConfigFileTools.hpp"

typedef struct tmp_s
{
    // It's very important to have no params constructor
    tmp_s() {
        this->test = "";
        this->test2 = 0;
    }
    std::string test;
    int test2;
} tmp_t;

std::any getTmp(const std::string &data)
{
    tmp_t value;

    if (!ConfigFileTools::matchWithRegex("^\\{.*\\}$", data))
        throw std::invalid_argument("Incorrect line format for TMP: " + data);
    try {
        std::vector<std::string> content = {
            data.substr(1, 17),
            data.substr(18, 13)
        };
        ConfigFile toRead(content);

        value.test = toRead.getVar<std::string>("test");
        value.test2 = toRead.getVar<int>("testD");
    } catch ([[maybe_unused]] const std::out_of_range &e) {
        throw std::invalid_argument("Invalide TMP: " + data);
    }
    return std::any(std::in_place_type<tmp_t>, value);
}

int main(int ac, char **av)
{
    if (ac != 2)
        return 84;
    ConfigFile conf(av[1]);

    std::cout << conf.getVar<int>("exampleInt") << std::endl;
    std::cout << conf.getVar<float>("exampleFloat") << std::endl;
    std::cout << conf.getVar<std::string>("exampleString") << std::endl;
    std::cout << (conf.getVar<bool>("exampleBool") ? "true" : "false") << std::endl;

    conf.setVarGetter<tmp_t>(getTmp);

    std::cout << conf.getVar<tmp_t>("exampleCustom").test << conf.getVar<tmp_t>("exampleCustom").test2 << std::endl;

    std::vector<int> list = conf.getVectorOf<int>("exampleCustomList");

    for (auto it : list)
        std::cout << it << std::endl;
    return 0;
}