/*
** EPITECH PROJECT, 2021
** AsioConnectionTCP.hpp
** File description:
** Network TCP implementation with Asio lib, according to IConnection interface
*/

#ifndef BABEL_ASIOCONNECTIONTCP_HPP
#define BABEL_ASIOCONNECTIONTCP_HPP

#include <iostream>
#include <functional>
#include <unordered_map>

#ifdef _WIN32
    #include <Windows.h>
#else
    #include <unistd.h>
#endif

#include <asio/error.hpp>
#include <mutex>
#include <thread>
#include "ANetwork.hpp"
#include "NetworkException.hpp"

namespace Network
{
    using asio::ip::tcp;

    template <std::size_t PACKETSIZE> class AsioConnectionTCP : public AAsioConnection<PACKETSIZE> {
      public:
        explicit AsioConnectionTCP(const bool server = false) : AAsioConnection<PACKETSIZE>(server)
        {
        }

        ~AsioConnectionTCP()
        {
            this->disconnectAll();
        }

        void disconnect(const std::string &ip, const std::size_t port) override
        {
            auto first(_socketConnections.begin());
            auto last(_socketConnections.end());
            auto connection(getConnection(ip, port));

            const std::scoped_lock<std::mutex> lock(AAsioConnection<PACKETSIZE>::_mutex);

            if (!connection)
                throw Network::invalidConnection("Network::invalidConnection::_baseMessageFormat", ip, port);
            first = std::find(first, last, connection);
            if (first == last)
                throw Network::invalidConnection("Network::invalidConnection::_baseMessageFormat", ip, port);
            AAsioConnection<PACKETSIZE>::disconnect(
                connection->remote_endpoint().address().to_string(), connection->remote_endpoint().port());
            if (first != last)
                for (auto i = first; ++i != last;)
                    if (!(*i == connection))
                        (void) std::move(*i);
        }

        void disconnectAll() override
        {
            const std::scoped_lock<std::mutex> lock(AAsioConnection<PACKETSIZE>::_mutex);

            AAsioConnection<PACKETSIZE>::disconnectAll();
            _socketConnections.clear();
        }

        std::tuple<std::array<char, PACKETSIZE>, std::size_t, std::string, std::size_t> receiveAny() override
        {
            //            const std::scoped_lock<std::mutex> lock(AAsioConnection<PACKETSIZE>::_mutex);

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
            //            const std::scoped_lock<std::mutex> lock(AAsioConnection<PACKETSIZE>::_mutex);

            std::pair<std::array<char, PACKETSIZE>, std::size_t> buf({0}, 0);
            auto connection(getConnection(ip, port));

            if (!connection)
                throw Network::invalidConnection("Network::invalidConnection::_baseMessageFormat", ip, port);
            //            return std::pair<std::array<char, PACKETSIZE>, std::size_t>({}, 0);

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
            for (auto &connection : _socketConnections) {
                send(buf, connection);
            }
        }

        void send(const std::array<char, PACKETSIZE> &buf, const std::string &ip, const std::size_t port) override
        {
            auto connection(getConnection(ip, port));

            if (!connection)
                throw Network::invalidConnection("Network::invalidConnection::_baseMessageFormat", ip, port);
            std::cout << "connection exists, need to send now" << std::endl;
            send(buf, connection);
        }

      protected:
        void send(const std::array<char, PACKETSIZE> &buf, std::shared_ptr<tcp::socket> &connection)
        {
            if (!connection)
                throw Network::invalidConnection();
            std::cout << "sending ..." << std::endl;
            connection->send(asio::buffer(std::string(buf.data(), buf.size())));
        }

        [[nodiscard]] bool isConnection(const std::shared_ptr<tcp::socket> &connection, const std::string &otherIp,
            const std::size_t otherPort) const
        {
            if (!connection)
                return false;
            auto endpoint(connection->remote_endpoint());

            if (endpoint.address().to_string() == otherIp && endpoint.port() == otherPort)
                return true;
            return false;
        }

        std::shared_ptr<tcp::socket> getConnection(const std::string &ip, const std::size_t port)
        {
            const std::scoped_lock<std::mutex> lock(AAsioConnection<PACKETSIZE>::_mutex);

            for (auto socketConnection : _socketConnections) {
                if (isConnection(socketConnection, ip, port)) {
                    return socketConnection;
                }
            }
            return nullptr;
        }

        /**
         * @brief Record a connection and be ready to receive data from it
         * @param newConnection The connection to record
         */
        void addConnection(std::shared_ptr<tcp::socket> &newConnection)
        {
            if (!newConnection)
                return;
            //            const std::scoped_lock<std::mutex> lock(AAsioConnection<PACKETSIZE>::_mutex);

            AAsioConnection<PACKETSIZE>::connect(
                newConnection->remote_endpoint().address().to_string(), newConnection->remote_endpoint().port());
            _socketConnections.push_back(newConnection);
            //            newConnection->set_option(_receiveBufferSizeOption); // TODO refactor PACKETSIZE
            //            newConnection->set_option(_sendBufferSizeOption);
            asyncReceive(newConnection);
        }

        /**
         * @brief Initialize asynchronous data acceptance from every
         * connection
         */
        void asyncReceiveAny()
        {
            for (auto &connection : _socketConnections) {
                asyncReceive(connection);
            }
        }

        /**
         * @brief Initialize asynchronous data acceptance from this
         * connection
         * @param connection The socket, where the data can come from
         */
        void asyncReceive(std::shared_ptr<tcp::socket> &connection)
        {
            //            const std::scoped_lock<std::mutex> lock(AAsioConnection<PACKETSIZE>::_mutex); // todo ensure
            //            that no
            // problem with callback

            if (!connection)
                return;

            std::cout << "\tWill now Receive from " << connection << std::endl;
            connection->async_receive(asio::buffer(AAsioConnection<PACKETSIZE>::_recvBuf.data(),
                                          AAsioConnection<PACKETSIZE>::_recvBuf.size()),
                std::bind(&AsioConnectionTCP<PACKETSIZE>::asyncReceiving,
                    this,
                    std::placeholders::_1,
                    std::placeholders::_2,
                    connection));
        }

        void asyncReceiving(
            const asio::error_code &err, const std::size_t &lenRecvBuf, std::shared_ptr<tcp::socket> &connection)
        {
            std::cout << "asyncReceiving()" << std::endl;
            if (err) {
                if (err.value() == asio::error::misc_errors::eof) {
                    std::cout << "\tAn error occured : asio::error::misc_errors" << std::endl;
                    return;
                }
            }
            std::cout << "\t\tNo error" << std::endl;
            if (!lenRecvBuf) {
                std::cout << "\t\t\tAn error occured : no lenRecvBuf" << std::endl;
                return;
            }

            if (!AAsioConnection<PACKETSIZE>::_recvBuf.data()) {
                return;
            }
            std::cout << "\t\t\t\t\tReceived data" << std::endl;
            AAsioConnection<PACKETSIZE>::_recvData.emplace(
                std::make_pair(
                    connection->remote_endpoint().address().to_string(), connection->remote_endpoint().port()),
                std::make_pair(AAsioConnection<PACKETSIZE>::_recvBuf, lenRecvBuf));
            asyncReceive(connection);
        }

      private:
        /**
         * @brief deque of connected sockets
         */
        std::deque<std::shared_ptr<tcp::socket>> _socketConnections;

        /**
         * @brief Option (to be set) to buffer data when receiving it
         */
        asio::socket_base::receive_buffer_size _receiveBufferSizeOption{PACKETSIZE};

        /**
         * @brief Option (to be set) to buffer data when sending it
         */
        //        asio::socket_base::send_buffer_size
        //        _sendBufferSizeOption{PACKETSIZE};
    };

} // namespace Network

#endif // BABEL_ASIOCONNECTIONTCP_HPP