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

#ifdef _WIN32
    #include <Windows.h>
#else
    #include <unistd.h>
#endif

#include <asio/error.hpp>
#include "ANetwork.hpp"

namespace Network
{
    using asio::ip::tcp;

    template <PointerableUnknownLen Data> class AsioConnectionTCP : public AAsioConnection<Data> {
      public:
        explicit AsioConnectionTCP(const bool server = false) : AAsioConnection<Data>(server)
        {
        }

        ~AsioConnectionTCP()
        {
            this->disconnectAll();
        }

        /**
         * @throw Network::invalidConnection if ip and port don't correspond to any connected machine
         */
        void disconnect(const std::string &ip, const std::size_t port) override
        {
            auto first(_socketConnections.begin());
            auto last(_socketConnections.end());
            auto connection(getConnection(ip, port));

            if (!connection)
                throw Network::invalidConnection(Network::invalidConnection::_baseMessageFormat, ip, port);
            first = std::find(first, last, connection);
            if (first == last)
                throw Network::invalidConnection(Network::invalidConnection::_baseMessageFormat, ip, port);
            this->send(Data(), ip, port);
            AAsioConnection<Data>::disconnect(
                connection->remote_endpoint().address().to_string(), connection->remote_endpoint().port());
            if (first != last)
                for (auto i = first; ++i != last;)
                    if (!(*i == connection))
                        (void) std::move(*i);
        }

        void disconnectAll() override
        {
            AAsioConnection<Data>::disconnectAll();

            for (const auto &connection : _socketConnections) {
                disconnect(connection->remote_endpoint().address().to_string(), connection->remote_endpoint().port());
            }
        }

        /**
         * @brief Receive data from connected machines
         * @return The data and its author, if received
         */
        std::tuple<Data, std::size_t, std::string, std::size_t> receiveAny() override
        {
            std::pair<Data, std::size_t> buf;

            for (const auto &connection : AAsioConnection<Data>::_connections) {
                buf = receive(connection.first, connection.second);

                if (buf.second != 0) {
                    return std::make_tuple(buf.first, buf.second, connection.first, connection.second);
                }
                /**
                 * @brief Write the good amount of data :
                 *  std::cout.write(recvBuf.data(), len);
                 */
            }

            //            return std::make_tuple(Data(), 0, "", 0);
            return {Data(), 0, "", 0};
        }

        /**
         * @brief Receive data from a particular machine
         * @param ip The ip of the machine to receive data from
         * @param port The port of the machine to receive data from
         * @return The data, if received
         * @throw Network::invalidConnection if ip and port don't correspond to any connected machine
         */
        std::pair<Data, std::size_t> receive(const std::string &ip, const std::size_t port) override
        {
            std::pair<Data, std::size_t> buf({}, 0);
            auto connection(getConnection(ip, port));

            if (!connection)
                throw Network::invalidConnection(Network::invalidConnection::_baseMessageFormat, ip, port);

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
            return std::pair<Data, std::size_t>({}, 0);
        }

        void sendAll(const Data &buf) override
        {
            for (auto &connection : _socketConnections) {
                send(buf, connection);
            }
        }

        /**
         * @throw Network::invalidConnection if ip and port don't correspond to any connected machine
         */
        void send(const Data &buf, const std::string &ip, const std::size_t port) override
        {
            auto connection(getConnection(ip, port));

            if (!connection)
                throw Network::invalidConnection(Network::invalidConnection::_baseMessageFormat, ip, port);
            send(buf, connection);
        }

      protected:
        /**
         * @throw Network::invalidConnection if ip and port don't correspond to any connected machine
         */
        void send(const Data &buf, std::shared_ptr<tcp::socket> &connection)
        {
            if (!connection)
                throw Network::invalidConnection();
            connection->send(asio::buffer(buf.serialize(), buf.length()));
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
            if (!connection)
                return;

            connection->async_receive(
                asio::buffer(AAsioConnection<Data>::_recvBuf.first, AAsioConnection<Data>::_recvBuf.second),
                std::bind(&AsioConnectionTCP<Data>::asyncReceiving, this, std::placeholders::_1, std::placeholders::_2,
                    connection));
        }

        void asyncReceiving(const asio::error_code &err, const std::size_t &receivedPacketSize,
            std::shared_ptr<tcp::socket> &connection)
        {
            if (err) {
                if (err.value() == asio::error::misc_errors::eof) {
                    return;
                }
            }
            if (!receivedPacketSize) {
                return;
            }
            AAsioConnection<Data>::_recvData.emplace(std::make_pair(connection->remote_endpoint().address().to_string(),
                                                         connection->remote_endpoint().port()),
                std::make_pair(Data(AAsioConnection<Data>::_recvBuf.first, receivedPacketSize), receivedPacketSize));
            asyncReceive(connection);
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

            AAsioConnection<Data>::connect(
                newConnection->remote_endpoint().address().to_string(), newConnection->remote_endpoint().port());
            _socketConnections.push_back(newConnection);
            asyncReceive(newConnection);
        }

      private:
        /**
         * @brief deque of connected sockets
         */
        ThreadSafety::LockedDeque<std::shared_ptr<tcp::socket>> _socketConnections;
    };

} // namespace Network

#endif // BABEL_ASIOCONNECTIONTCP_HPP