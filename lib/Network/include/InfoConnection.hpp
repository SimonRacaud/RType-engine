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
        std::string ip;
        size_t port;
    };
}

#endif // INFOCONNECTION_HPP
