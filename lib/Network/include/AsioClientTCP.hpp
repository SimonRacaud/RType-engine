/*
** EPITECH PROJECT, 2021
** AsioClientTCP.hpp
** File description:
** Implementation of Client for TCP protocol
*/
#ifndef BABEL_ASIOCLIENTTCP_HPP
#define BABEL_ASIOCLIENTTCP_HPP

#include <iostream>
#include "AsioConnectionTCP.hpp"
#include "utils/Clock.hpp"

namespace Network
{
    static const double ConnectionPingInterval(3);

    template <std::size_t PACKETSIZE> class AsioClientTCP : public AsioConnectionTCP<PACKETSIZE> {
      public:
        AsioClientTCP() = default;

        bool connect(const std::string &ip, const std::size_t port) override
        {
            tcp::endpoint serverEndpoint(asio::ip::make_address(ip), port);
            auto newConnection(std::make_shared<tcp::socket>(AAsioConnection<PACKETSIZE>::_ioContext));

            try {
                newConnection->connect(serverEndpoint);
            } catch (const std::system_error &) {
                std::cerr << "Failed to connect with server" << std::endl;
                _connectionTimer.setElapsedTime();
                if (_ping.count() > _connectionTimer.getElapsedTime().count()) {
                    std::this_thread::sleep_for(_ping - _connectionTimer.getElapsedTime());
                    _connectionTimer.resetStartingPoint();
                }
                return false;
            }
            AsioConnectionTCP<PACKETSIZE>::addConnection(newConnection);
            return true;
        }

      private:
        Clock _connectionTimer;
        const std::chrono::duration<double> _ping{ConnectionPingInterval};
    };

} // namespace Network

#endif // BABEL_ASIOCLIENTTCP_HPP