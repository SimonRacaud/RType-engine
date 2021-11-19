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

#include <cstddef>
#include <string>
#include <utility>

namespace Network
{
    struct InfoConnection {
        InfoConnection() = default;
        InfoConnection(InfoConnection const& other): ip(other.ip), port(other.port) {}

        InfoConnection(std::string const &ip, size_t port) : ip(ip), port(port) {}

        bool operator==(InfoConnection const &other) const
        {
            return other.ip == this->ip && other.port == this->port;
        }

        ~InfoConnection() = default;

        InfoConnection &operator=(const InfoConnection &rhs)
        {
            this->ip = rhs.ip;
            this->port = rhs.port;

            return *this;
        }

        std::string ip;
        size_t port{0};
    };
} // namespace Network

#endif // INFOCONNECTION_HPP