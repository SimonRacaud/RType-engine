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
    //    static const double ConnectionPingInterval(3);

    template <PointerableUnknownLen Data> class AsioClientTCP : public AsioConnectionTCP<Data> {
      public:
        /*      explicit AsioClientTCP(const std::size_t port) : AsioConnectionTCP<Data>(false),
                    _acceptor(AAsioConnection<Data>::_ioContext, tcp::endpoint(tcp::v4(), port)){
                  startAccept();

              };

              bool connect(const std::string &ip, const std::size_t port) override
              {
                  if (AAsioConnection<Data>::isConnected(ip, port)) {
                      return true;
                  }
                  tcp::endpoint serverEndpoint(asio::ip::make_address(ip), port);
                  auto newConnection(std::make_shared<tcp::socket>(AAsioConnection<Data>::_ioContext));

                  try {
                      newConnection->connect(serverEndpoint);
                  } catch (const std::system_error &) {
                      std::cerr << "TCP client Asio : Failed to connect with server" << std::endl;
                      _connectionTimer.setElapsedTime();
                      if (_ping.count() > _connectionTimer.getElapsedTime().count()) {
                          std::this_thread::sleep_for(_ping - _connectionTimer.getElapsedTime());
                          _connectionTimer.resetStartingPoint();
                      }
                      return false;
                  }

                  std::cout << "connecting with : ip :" << newConnection->local_endpoint().address().to_string()
                            << ", port : " << newConnection->local_endpoint().port() << std::endl;

                  AsioConnectionTCP<Data>::addConnection(newConnection);
                  return true;
              }

              void startAccept()
              {
                  std::shared_ptr<tcp::socket> newConnection(
                      std::make_shared<tcp::socket>(AAsioConnection<Data>::_ioContext));

                  _acceptor.async_accept(*newConnection,
                      std::bind(&AsioClientTCP::registerConnection, this, newConnection, std::placeholders::_1));
              }

              void registerConnection(std::shared_ptr<tcp::socket> newConnection, const asio::error_code &error)
              {
                  if (error) {
                      std::cerr << "TCP server Asio : " << error.message() << std::endl;
                  } else {
                      AsioConnectionTCP<Data>::addConnection(newConnection);
                  }

                  startAccept();
              }

            private:
              Clock _connectionTimer;
              const std::chrono::duration<double> _ping{ConnectionPingInterval};

              tcp::acceptor _acceptor;
      */
    };

} // namespace Network

#endif // BABEL_ASIOCLIENTTCP_HPP