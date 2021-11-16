/*
** EPITECH PROJECT, 2021
** AsioUdpServer.hpp
** File description:
** Network UDP implementation with Asio lib, according to IConnection interface
*/
#ifndef BABEL_ASIOCONNECTIONUDP_HPP
#define BABEL_ASIOCONNECTIONUDP_HPP

#include <algorithm>
#include <iostream>
#include "ANetwork.hpp"

namespace Network
{
    using asio::ip::udp;

    template <PointerableUnknownLen Data> class AsioConnectionUDP : public AAsioConnection<Data> {
      public:
        /**
         * @brief
         * @param port The port to open on this machine
         */
        explicit AsioConnectionUDP(const std::size_t port)
            : AAsioConnection<Data>(true),
              _endpoint(udp::v4(), port), _socket{AAsioConnection<Data>::_ioContext, _endpoint}
        {
            asyncReceiveAny();
        }

        ~AsioConnectionUDP()
        {
            disconnectAll();
        };

        bool connect(const std::string &ip, const std::size_t port) override
        {
            AAsioConnection<Data>::connect(ip, port);

            asyncReceive(ip, port);
            return true;
        }

        void disconnect(const std::string &ip, const std::size_t port) override
        {
            AAsioConnection<Data>::disconnect(ip, port);

            this->send(Data(), ip, port);
        }

        void disconnectAll() override
        {
            for (const auto &item : AAsioConnection<Data>::_connections) {
                disconnect(item.first, item.second);
            }
        }

        std::tuple<Data, std::size_t, std::string, std::size_t> receiveAny() override
        {
            if (!AAsioConnection<Data>::_recvData.empty()) {
                auto buf = AAsioConnection<Data>::_recvData.extract(AAsioConnection<Data>::_recvData.begin());

                return std::make_tuple(buf.second.first, buf.second.second, buf.first.first, buf.first.second);
            }
            /**
             * @brief Write the good amount of data :
             *  std::cout.write(recvBuf.data(), len);
             */

            return std::make_tuple(Data(), 0, "", 0);
        }

        std::pair<Data, std::size_t> receive(const std::string &ip, const std::size_t port) override
        {
            std::pair<Data, std::size_t> buf({}, 0);

            auto my_recvData(std::find_if(AAsioConnection<Data>::_recvData.begin(),
                AAsioConnection<Data>::_recvData.end(), [&](const auto &recvData) {
                    if (ip == recvData.first.first && port == recvData.first.second) {
                        return true;
                    }
                    return false;
                }));
            if (my_recvData != AAsioConnection<Data>::_recvData.end()) {
                buf = std::make_pair(my_recvData->second.first, my_recvData->second.second);
                AAsioConnection<Data>::_recvData.erase(my_recvData);
                return buf;
            }
            return buf;
        }

        void sendAll(const Data &buf) override
        {
            for (const auto &connection : AAsioConnection<Data>::_connections) {
                send(buf, connection.first, connection.second);
            }
        }

        void send(const Data &buf, const std::string &ip, const std::size_t port) override
        {
            udp::endpoint remoteEndpoint(asio::ip::make_address(ip), port);

            _socket.send_to(
                asio::buffer(buf.serialize(), buf.length()), remoteEndpoint, 0, AAsioConnection<Data>::_error);
        }

      private:
        /**
         * @brief Initialize asynchronous data acceptance from every connection
         */
        void asyncReceiveAny()
        {
            _socket.async_receive(
                asio::buffer(AAsioConnection<Data>::_recvBuf.first, AAsioConnection<Data>::_recvBuf.second),
                std::bind(&AsioConnectionUDP<Data>::asyncReceiving, this, std::placeholders::_1, std::placeholders::_2,
                    "",
                    0)); // todo find a way to get the address of the sender
                         //     in order to put it into ret val of receiveAny and to connect()
        }

        /**
         * @brief Initialize asynchronous data acceptance from this connection
         * @param connection The socket, where the data can come from
         */
        void asyncReceive(const std::string &ip, const std::size_t port)
        {
            asio::ip::udp::endpoint senderEndpoint(asio::ip::make_address(ip), port);

            _socket.async_receive_from(
                asio::buffer(AAsioConnection<Data>::_recvBuf.first, AAsioConnection<Data>::_recvBuf.second),
                senderEndpoint,
                std::bind(&AsioConnectionUDP<Data>::asyncReceiving, this, std::placeholders::_1, std::placeholders::_2,
                    ip, port));
        }

        void asyncReceiving(const asio::error_code &err, const std::size_t &receivedPacketSize, const std::string &ip,
            const std::size_t port)
        {
            if (err) {
                if (err.value() == asio::error::misc_errors::eof) {
                    // todo will be caught instead of the next if when disconnect() ?
                    return;
                }
            }
            if (!receivedPacketSize) {
                if (!ip.empty() && port) {
                    this->disconnect(ip, port);
                }
                return;
            }

            AAsioConnection<Data>::_recvData.emplace(std::make_pair(ip, port),
                std::make_pair(Data(AAsioConnection<Data>::_recvBuf.first, receivedPacketSize), receivedPacketSize));
            if (!ip.empty() && port)
                asyncReceive(ip, port);
        }

      private:
        udp::endpoint _endpoint;
        udp::socket _socket;
    };

} // namespace Network

#endif // BABEL_ASIOCONNECTIONUDP_HPP