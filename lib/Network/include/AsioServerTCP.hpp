/*
** EPITECH PROJECT, 2021
** AsioServerTCP.hpp
** File description:
** Implementation of Server for TCP protocol
*/
#ifndef BABEL_ASIOSERVERTCP_HPP
#define BABEL_ASIOSERVERTCP_HPP

#include "AsioConnectionTCP.hpp"

namespace Network
{
    template <std::size_t PACKETSIZE> class AsioServerTCP : public AsioConnectionTCP<PACKETSIZE> {
      public:
        /**
         * @brief
         * @param port The port to open on this machine
         * @throws system_error if port is already used
         */
        explicit AsioServerTCP(const std::size_t port)
            : AsioConnectionTCP<PACKETSIZE>(true),
              _acceptor(AAsioConnection<PACKETSIZE>::_ioContext, tcp::endpoint(tcp::v4(), port))
        {
            startAccept();
        }

      private:
        void startAccept()
        {
            std::shared_ptr<tcp::socket> newConnection(
                std::make_shared<tcp::socket>(AAsioConnection<PACKETSIZE>::_ioContext));

            _acceptor.async_accept(*newConnection,
                std::bind(&AsioServerTCP::registerConnection, this, newConnection, std::placeholders::_1));
        }

        void registerConnection(std::shared_ptr<tcp::socket> newConnection, const asio::error_code &error)
        {
            if (error)
                return; // todo check errors

            AsioConnectionTCP<PACKETSIZE>::addConnection(newConnection);

            startAccept();
        }

      private:
        tcp::acceptor _acceptor;
    };

} // namespace Network

#endif // BABEL_ASIOSERVERTCP_HPP