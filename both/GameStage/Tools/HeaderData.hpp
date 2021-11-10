/*
** EPITECH PROJECT, 2021
** HeaderData
** File description:
** HeaderData.hpp
*/

#ifndef HEADERDATA_HPP
#define HEADERDATA_HPP

#include <string>

class HeaderData
{
    public:
        HeaderData(): lvl(0), background("") {}
        HeaderData(std::size_t srcLvl, const std::string &srcBack): lvl(srcLvl), background(srcBack) {}
        ~HeaderData() = default;

        std::size_t lvl;
        std::string background;
};

#endif