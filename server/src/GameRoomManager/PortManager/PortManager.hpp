/*
** EPITECH PROJECT , 2021
** PortManager
** File description:
** PortManager.hpp
*/

#ifndef PORTMANAGER_HPP
#define PORTMANAGER_HPP

#include <tuple>

class PortManager
{
    public:
        using PortType = int;
        using PortPageType = std::pair<PortType, PortType>;

    public:
        PortManager(PortPageType);
        ~PortManager() = default;

        PortType getPort();
        bool isAlreadyDeliver(PortType);

    private:
        PortType _current;
        PortPageType _page;
};

#endif