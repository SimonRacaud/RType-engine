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
#include <cstddef>

namespace Network {
    struct InfoConnection {
        InfoConnection() = default;
        InfoConnection(std::string const &ip, size_t port) : ip(ip), port(port) {}
        bool operator==(InfoConnection const &other) {
            return other.ip == this->ip && other.port == this->port;
        }

        std::string ip;
        size_t port{0};
    };
}

#endif // INFOCONNECTION_HPP