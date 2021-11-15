/*
** EPITECH PROJECT , 2021
** InfoConnection
** File description:
** \file InfoConnection.hpp
** \author simon
** \brief
** \date 15/11/2021
*/

#ifndef INFOCONNECTION_HPP
#define INFOCONNECTION_HPP

#include <string>
#include <stddef.h>

namespace Network {
    struct InfoConnection {
        InfoConnection(std::string const &ip, size_t port) : ip(ip), port(port) {}

        std::string ip;
        size_t port;
    };
}

#endif // INFOCONNECTION_HPP
