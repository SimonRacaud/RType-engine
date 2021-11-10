/*
** EPITECH PROJECT, 2021
** INetwork.hpp
** File description:
** Network interface
*/

#ifndef BABEL_NETWORK_HPP
#define BABEL_NETWORK_HPP

#include <array>
#include <cstddef>
#include <queue>
#include <string>
#include <tuple>
#include <utility>
#include <vector>

#include "asio.hpp"
#include "utils/Concepts/Pointerable.hpp"

namespace Network
{
    enum protocol { TCP, UDP };

    template <Pointerable Data> class IConnection {
      public:
        /**
         * @brief Connect to a remote INetwork class
         * @param ip The ip of the targeted machine
         * @param port The port of the targeted machine
         * @return true if connected, false otherwise
         */
        virtual bool connect(const std::string &ip, const std::size_t port) = 0;

        /**
         * @brief Disconnect from a particular machine
         * @param ip The machine's ip address
         * @param port The machine's port
         */
        virtual void disconnect(const std::string &ip, const std::size_t port) = 0;
        /**
         * @brief Disconnect from every connected machine
         */
        virtual void disconnectAll() = 0;

        /**
         * @brief Receive data from any machine connected
         * @return The first data caught, its length, and infos about the
         * sender (ip and port)
         */
        virtual std::tuple<Data, std::size_t, std::string, std::size_t> receiveAny() = 0;
        /**
         * @brief Receive data from a particular machine
         * @param ip The machine's ip address
         * @param number The machine's port number
         * @return The data received, '\0's if nothing received
         */
        virtual std::pair<Data, std::size_t> receive(const std::string &ip, const std::size_t port) = 0;

        /**
         * @brief Send data to every machine connected
         * @param buf The data in a binary form
         */
        virtual void sendAll(const Data &buf) = 0;

        /**
         * @brief Send data to a particular machine
         * @param buf The data sent
         * @param ip The machine's ip address
         * @param port The machine's port number
         */
        virtual void send(const Data &buf, const std::string &ip, const std::size_t port) = 0;

        /**
         * @brief Check if a machine is connected
         * @param ip The machine's ip address
         * @param port The machine's port number
         * @return True if connected, false otherwise
         */
        [[nodiscard]] virtual bool isConnected(const std::string &ip, const std::size_t port) const = 0;
    };

} // namespace Network

#endif // BABEL_NETWORK_HPP