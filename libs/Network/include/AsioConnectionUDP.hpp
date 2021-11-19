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
#include "asio/placeholders.hpp"

#include "asio/error_code.hpp"
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
            : AAsioConnection<Data>(true), _socket{AAsioConnection<Data>::_ioContext, udp::endpoint(udp::v4(), port)}
        {
            asyncReceiveAny();
        }

        ~AsioConnectionUDP()
        {
            disconnectAll();
        };

        bool connect(const std::string &ip, const std::size_t port) override
        {
            if (AAsioConnection<Data>::isConnected(ip, port)) {
                return true;
            } else {
                sendPing(ip, port);
                return AAsioConnection<Data>::connect(ip, port);
            }
        }

        void disconnect(const std::string &ip, const std::size_t port) override
        {
            if (!AAsioConnection<Data>::isConnected(ip, port)) {
                return;
            }

            sendPing(ip, port);
            AAsioConnection<Data>::disconnect(ip, port);
        }

        void disconnectAll() override
        {
            for (const auto &item : AAsioConnection<Data>::_connections) {
                disconnect(item.ip, item.port);
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
                send(buf, connection.ip, connection.port);
            }
        }

        void send(const Data &buf, const std::string &ip, const std::size_t port) override
        {
            udp::endpoint remoteEndpoint(asio::ip::make_address(ip), port);

            if (buf.length()) {
                auto buffer = asio::buffer(buf.serialize(), buf.length());
                _socket.send_to(buffer, remoteEndpoint, 0, AAsioConnection<Data>::_error);
            }
        }

      private:
        void sendPing(const std::string &ip, const std::size_t port)
        {
            udp::endpoint remoteEndpoint(asio::ip::make_address(ip), port);
            asio::const_buffer buffer(nullptr, 0);

            _socket.send_to(buffer, remoteEndpoint, 0, AAsioConnection<Data>::_error);
        }
        /**
         * @brief Initialize asynchronous data acceptance from every connection
         */
        void asyncReceiveAny()
        {
            _socket.async_receive_from(
                asio::buffer(AAsioConnection<Data>::_recvBuf.first, AAsioConnection<Data>::_recvBuf.second),
                _senderEndpoint,
                std::bind(
                    &AsioConnectionUDP<Data>::asyncReceiving, this, std::placeholders::_1, std::placeholders::_2));
        }

        void asyncReceiving(const asio::error_code &err, const std::size_t &receivedPacketSize)
        {
            auto senderIp(_senderEndpoint.address().to_string());
            auto senderPort(_senderEndpoint.port());

            if (err) {
                std::cerr << "UDP Asio : " << err.message() << std::endl;
                if (err.value() == asio::error::operation_aborted) {
                    resetReceive();
                    if (AAsioConnection<Data>::isConnected(senderIp, senderPort)) {
                        AAsioConnection<Data>::disconnect(senderIp, senderPort);
                    }
                    return;
                }
            }

            if (!receivedPacketSize && !senderIp.empty() && senderPort) {
                if (AAsioConnection<Data>::isConnected(senderIp, senderPort)) {
                    AAsioConnection<Data>::disconnect(senderIp, senderPort);
                } else {
                    AAsioConnection<Data>::connect(senderIp, senderPort);
                }
                resetReceive();
                return;
            }

            AAsioConnection<Data>::_recvData.emplace(std::make_pair(senderIp, senderPort),
                std::make_pair(Data(AAsioConnection<Data>::_recvBuf.first, receivedPacketSize), receivedPacketSize));
            resetReceive();
        }

        void resetReceive()
        {
            memset(AAsioConnection<Data>::_recvBuf.first, 0, AAsioConnection<Data>::_recvBuf.second);
            asyncReceiveAny();
        }

      private:
        udp::endpoint _senderEndpoint;
        udp::socket _socket;
    };

} // namespace Network

#endif // BABEL_ASIOCONNECTIONUDP_HPP