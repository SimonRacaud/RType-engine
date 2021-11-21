/*
** EPITECH PROJECT, 2021
** AsioConnectionTCP.hpp
** File description:
** Network TCP implementation with Asio lib, according to IConnection interface
*/

#ifndef ASIOCONNECTIONTCP_HPP
#define ASIOCONNECTIONTCP_HPP

#include <functional>
#include <iostream>

#ifdef _WIN32
    #include <asio.hpp>
#else
    #include <unistd.h>
#endif

#include <asio/error.hpp>
#include "Asio/ANetwork.hpp"
#include "utils/Clock.hpp"

namespace Network
{
    using asio::ip::tcp;

    static const double ConnectionPingInterval(0);

    template <PointerableUnknownLen Data> class AsioConnectionTCP : public AAsioConnection<Data> {
      public:
        explicit AsioConnectionTCP(const std::size_t port, const bool server = false)
            : AAsioConnection<Data>(server),
              _acceptor(AAsioConnection<Data>::_ioContext, tcp::endpoint(tcp::v4(), port))
        {
            startAccept();
        }

        ~AsioConnectionTCP()
        {
            this->disconnectAll();
        }
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
        /**
         * @throw Network::invalidConnection if ip and port don't correspond to any connected machine
         */
        void disconnect(const std::string &ip, const std::size_t port) override
        {
            auto connection(getConnection(ip, port));

            if (!connection) {
                throw Network::invalidConnection(Network::invalidConnection::_baseMessageFormat, ip, port);
            }
            disconnect(connection);
        }

        void disconnectAll() override
        {
            for (auto &connection : _socketConnections) {
                disconnect(connection);
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
                buf = receive(connection.ip, connection.port);

                if (buf.second != 0) {
                    return std::make_tuple(buf.first, buf.second, connection.ip, connection.port);
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
            if (_socketConnections.empty()) {
                throw std::runtime_error("AsioConnectionTCP::sendAll No connection available.");
            }
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
            std::cout << "sending from low level : " << connection->remote_endpoint().address().to_string() << "< ;"
                      << connection->remote_endpoint().port() << std::endl;
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
                std::cerr << "TCP Asio : " << err.message() << std::endl;
                if (err.value() == asio::error::operation_aborted) {
                    disconnect(connection);
                    return;
                }
                if (err.value() == asio::error::misc_errors::eof) {
                    disconnect(connection);
                    return;
                }
            }
            std::cout << "received from low level" << std::endl;

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
            try {
                auto endpoint(connection->remote_endpoint());

                if (endpoint.address().to_string() == otherIp && endpoint.port() == otherPort)
                    return true;
            } catch (...) {
            }
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
            _socketConnections.emplace_back(newConnection);
            asyncReceive(newConnection);
        }

      private:
        void startAccept()
        {
            std::shared_ptr<tcp::socket> newConnection(
                std::make_shared<tcp::socket>(AAsioConnection<Data>::_ioContext));

            _acceptor.async_accept(*newConnection,
                std::bind(&AsioConnectionTCP::registerConnection, this, newConnection, std::placeholders::_1));
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

        void disconnect(std::shared_ptr<tcp::socket> &connection)
        {
            asio::ip::tcp::endpoint connectionEndpoint;
            std::string connectionIp;
            std::size_t connectionPort(0);

            try {
                connectionEndpoint = connection->remote_endpoint();
                connectionIp = connectionEndpoint.address().to_string();
                connectionPort = connectionEndpoint.port();
                if (AAsioConnection<Data>::isConnected(connectionIp, connectionPort))
                    AAsioConnection<Data>::disconnect(connectionIp, connectionPort);
            } catch (const std::system_error &) {
            }
            if (connection && connection->is_open()) {
                try {
                    connection->close();
                } catch (const std::system_error &) {
                }
            }
            auto pos(std::find(_socketConnections.begin(), _socketConnections.end(), connection));
            if (pos != _socketConnections.end()) {
                _socketConnections.erase(pos);
            }
        }

      private:
        /**
         * @brief deque of connected sockets
         */
        ThreadSafety::LockedDeque<std::shared_ptr<tcp::socket>> _socketConnections;

        tcp::acceptor _acceptor;

        Clock _connectionTimer;
        const std::chrono::duration<double> _ping{ConnectionPingInterval};
    };

} // namespace Network

#endif // ASIOCONNECTIONTCP_HPP