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

    template <std::size_t PACKETSIZE> class AsioConnectionUDP : public AAsioConnection<PACKETSIZE> {
      public:
        /**
         * @brief
         * @param port The port to open on this machine
         */
        explicit AsioConnectionUDP(const std::size_t port)
            : AAsioConnection<PACKETSIZE>(true),
              _endpoint(udp::v4(), port), _socket{AAsioConnection<PACKETSIZE>::_ioContext, _endpoint}
        {
        }

        ~AsioConnectionUDP() = default;

        bool connect(const std::string &ip, const std::size_t port) override
        {
            AAsioConnection<PACKETSIZE>::connect(ip, port);

            asyncReceive(ip, port);
            return true;
        }

        std::tuple<std::array<char, PACKETSIZE>, std::size_t, std::string, std::size_t> receiveAny() override
        {
            std::pair<std::array<char, PACKETSIZE>, std::size_t> buf;

            for (const auto &connection : AAsioConnection<PACKETSIZE>::_connections) {
                buf = receive(connection.first, connection.second);

                if (buf.second != 0) {
                    return std::make_tuple(buf.first, buf.second, connection.first, connection.second);
                }
                /**
                 * @brief Write the good amount of data :
                 *  std::cout.write(recvBuf.data(), len);
                 */
            }

            return std::make_tuple(std::array<char, PACKETSIZE>(), 0, "", 0);
        }

        std::pair<std::array<char, PACKETSIZE>, std::size_t> receive(
            const std::string &ip, const std::size_t port) override
        {
            //            std::cout << std::endl << std::endl << "receive()" << std::endl;
            std::pair<std::array<char, PACKETSIZE>, std::size_t> buf({0}, 0);
            //            _socket.set_option(_receiveBufferSizeOption); // TODO refactor PACKETSIZE

            auto my_recvData(std::find_if(AAsioConnection<PACKETSIZE>::_recvData.begin(),
                AAsioConnection<PACKETSIZE>::_recvData.end(),
                [&](const auto &recvData) {
                    if (ip == recvData.first.first && port == recvData.first.second) {
                        return true;
                    }
                    return false;
                }));
            if (my_recvData != AAsioConnection<PACKETSIZE>::_recvData.end()) {
                buf = std::make_pair(my_recvData->second.first, my_recvData->second.second);
                AAsioConnection<PACKETSIZE>::_recvData.erase(my_recvData);
                return buf;
            }
            return std::pair<std::array<char, PACKETSIZE>, std::size_t>({}, 0);
        }

        void sendAll(const std::array<char, PACKETSIZE> &buf) override
        {
            for (const auto &connection : AAsioConnection<PACKETSIZE>::_connections) {
                std::cout << "UDP sending to : " << std::endl;
                std::cout << "ip : " << connection.first << std::endl;
                std::cout << "port : " << connection.second << std::endl;
                send(buf, connection.first, connection.second);
            }
        }

        void send(const std::array<char, PACKETSIZE> &buf, const std::string &ip, const std::size_t port) override
        {
            std::cout << std::endl << "sending" << std::endl;
            udp::endpoint remoteEndpoint(asio::ip::make_address(ip), port);

            _socket.send_to(asio::buffer(buf), remoteEndpoint, 0, AAsioConnection<PACKETSIZE>::_error);
        }

        void runAsync()
        {
            //            asyncReceiveAny();
            AAsioConnection<PACKETSIZE>::runAsync();
            // todo add asyncReceive for each new connection started !!!!!
        }

      private:
        /**
         * @brief Initialize asynchronous data acceptance from every connection
         */
        void asyncReceiveAny()
        {
            for (auto &connection : AAsioConnection<PACKETSIZE>::_connections) {
                asyncReceive(connection.first, connection.second);
            }
        }

        /**
         * @brief Initialize asynchronous data acceptance from this connection
         * @param connection The socket, where the data can come from
         */
        void asyncReceive(const std::string &ip, const std::size_t port)
        {
            std::cout << "will now receive from new connection : " << ip << " : " << port
                      << std::endl; // todo remove after debug

            asio::ip::udp::endpoint senderEndpoint(asio::ip::make_address(ip), port);

            _socket.async_receive_from(asio::buffer(AAsioConnection<PACKETSIZE>::_recvBuf),
                senderEndpoint,
                std::bind(&AsioConnectionUDP<PACKETSIZE>::asyncReceiving,
                    this,
                    std::placeholders::_1,
                    std::placeholders::_2,
                    ip,
                    port));
        }

        void asyncReceiving(
            const asio::error_code &err, const std::size_t &lenRecvBuf, const std::string &ip, const std::size_t port)
        {
            std::cout << "receiving..." << std::endl;
            if (err) {
                if (err.value() == asio::error::misc_errors::eof) {
                    return;
                }
            }
            // std::cout << "no error" << std::endl;
            if (!lenRecvBuf) {
                return;
            }
            std::cout << "Buff is " << lenRecvBuf << " of length" << std::endl;
            if (!AAsioConnection<PACKETSIZE>::_recvBuf.data()) {
                return;
            }
            std::cout << "received data from : " << std::endl;
            std::cout << "ip : " << ip << std::endl;
            std::cout << "port : " << port << std::endl;
            AAsioConnection<PACKETSIZE>::_recvData.emplace(
                std::make_pair(ip, port), std::make_pair(AAsioConnection<PACKETSIZE>::_recvBuf, lenRecvBuf));
            std::cout << "data stored in buffer" << std::endl;
            asyncReceive(ip, port);
        }

      private:
        udp::endpoint _endpoint;
        udp::socket _socket;

        asio::socket_base::receive_buffer_size _receiveBufferSizeOption{PACKETSIZE};
    };

} // namespace Network

#endif // BABEL_ASIOCONNECTIONUDP_HPP