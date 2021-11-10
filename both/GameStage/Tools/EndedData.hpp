/*
** EPITECH PROJECT, 2021
** EndedData
** File description:
** EndedData.hpp
*/

#ifndef ENDEDDATA_HPP
#define ENDEDDATA_HPP

#include <string>

class EndedData
{
    public:
        EndedData() : nextStage("") {}
        EndedData(const std::string &src) : nextStage(src) {}
        ~EndedData() = default;

        std::string nextStage;
};

#endif