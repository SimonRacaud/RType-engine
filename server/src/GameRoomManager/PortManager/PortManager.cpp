/*
** EPITECH PROJECT , 2021
** PortManager
** File description:
** PortManager.hpp
*/

#include <stdexcept>
#include "PortManager.hpp"

PortManager::PortManager(PortPageType page) : _current(page.first), _page(page)
{
    if (page.first >= page.second)
        throw std::invalid_argument("Invalid port page");
}

PortManager::PortType PortManager::getPort()
{
    PortType port = _current;

    if (port > _page.second)
        throw std::invalid_argument("No more port available");
    _current++;
    return port;
}

bool PortManager::isAlreadyDeliver(PortManager::PortType ref)
{
    return ref < _current;
}