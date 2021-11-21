/*
** EPITECH PROJECT, 2021
** ANetwork.hpp
** File description:
** Network Abstract class
*/
#ifndef BABEL_ANETWORK_HPP
#define BABEL_ANETWORK_HPP

#include <functional>
#include <iostream>
#include <thread>
#include "Exceptions/NetworkException.hpp"
#include "INetwork.hpp"
#include "utils/ThreadSafety/LockedUnorderedMultimap.hpp"

#ifndef MY_MAP
    #define MY_MAP
struct hash_pair {
    std::size_t operator()(const std::pair<std::string, std::size_t> &pair) const
    {
        std::size_t h1 = std::hash<std::string>{}(pair.first);
        std::size_t h2 = std::hash<std::size_t>{}(pair.second);

        return h1 ^ h2;
    }
};
#endif

namespace Network
{
    template <PointerableUnknownLen Data> class AAsioConnection : public IConnection<Data> {
      public:
        explicit AAsioConnection(const bool server = false) : _server(server)
        {
            runAsync();
        }

        virtual ~AAsioConnection()
        {
            delete[] _recvBuf.first;
            _recvBuf.first = nullptr;
            stopRunAsync();
            disconnectAll();
        }

        AAsioConnection &operator=(const AAsioConnection<Data> &) = delete;
        AAsioConnection(const AAsioConnection<Data> &) = delete;

        bool connect(const std::string &ip, const std::size_t port) override
        {
            AAsioConnection<Data>::_connections.emplace_back(ip, port);
            return true;
        }

        /**
         * @throw Network::invalidConnection if ip and port don't correspond to any connected machine
         */
        void disconnect(const std::string &ip, const std::size_t port) override
        {
            auto first(_connections.begin());
            auto last(_connections.end());
            Network::InfoConnection value(ip, port);

            first = std::find(first, last, value);
            if (first == last)
                throw Network::invalidConnection(Network::invalidConnection::_baseMessageFormat, ip, port);
            _connections.erase(first);
        }

        void disconnectAll() override
        {
            AAsioConnection<Data>::_connections.clear();
        }

        std::tuple<Data, std::size_t, std::string, std::size_t> receiveAny() override = 0;

        std::pair<Data, std::size_t> receive(const std::string &ip, const std::size_t port) override = 0;

        void sendAll(const Data &buf) override = 0;

        void send(const Data &buf, const std::string &ip, const std::size_t port) override = 0;

        [[nodiscard]] bool isConnected(const std::string &ip, const std::size_t port) const override
        {
            if (!AAsioConnection<Data>::_connections.empty()
                && std::find_if(_connections.begin(), _connections.end(),
                       [=](const auto &connection) {
                           return ip == connection.ip && port == connection.port;
                       })
                    != AAsioConnection<Data>::_connections.end()) {
                return true;
            }
            return false;
        }

        const ThreadSafety::LockedDeque<Network::InfoConnection> &getConnections() const override
        {
            return _connections;
        }

      private:
        // Asynchronous operations
        /**
         * @brief Create a thread, which will execute asynchronous actions on
         *  network (accept connections and receive data)
         */
        void runAsync()
        {
            if (_thread.joinable())
                return;
            _thread = std::thread(&AAsioConnection<Data>::realRunAsync, this);
        }

        /**
         * @brief loop through awaiting asynchronous actions and stop if one is
         *  done to be called every time a connection or data is to be received
         */
        void realRunAsync()
        {
            _runningAsync = true;
            const std::chrono::duration<double> waitAsyncSetup(0.01);

            std::this_thread::sleep_for(waitAsyncSetup);
            while (_thread.joinable() && _runningAsync) {
                _ioContext.run_one_for(std::chrono::seconds(1));
                // todo might not work for big packets
            }
        }

        void stopRunAsync()
        {
            _runningAsync = false;
            if (!_thread.joinable()) {
                return;
            }
            if (!AAsioConnection<Data>::_ioContext.stopped()) {
                AAsioConnection<Data>::_ioContext.stop();
            }
            if (_thread.joinable())
                _thread.join();
        }

      protected:
        /**
         * @property Run asio asynchronous operations in a blocking way
         */
        asio::io_context _ioContext;

        /**
         * @property _error Transmit error message
         */
        asio::error_code _error;

        /**
         * @property _type Know the type of protocol to use
         */
        enum protocol _type = protocol::TCP;

        /**
         * @property _server True if a server, false if a client
         */
        bool _server;

        /**
         * @property _packetSize The size that is read from the socket when receiving
         */
        std::size_t _receivePacketSize{500};
        // todo change

        ThreadSafety::LockedDeque<Network::InfoConnection> _connections;

        // Asynchronous operations
        bool _runningAsync{false};
        /**
         * @property Contain data received from connections through
         *  asynchronous operations
         * @note std::atomic ensures thread safety over this variable
         */
        ThreadSafety::LockedUnorderedMultimap<std::pair<const std::string, const std::size_t>,
            std::pair<Data, std::size_t>, hash_pair>
            _recvData;
        /**
         * @property Run asynchronous asio operations in a non-blocking way
         */
        std::thread _thread;
        /**
         * @note std::atomic ensures thread safety over this variable
         */
        //        std::pair<Data, std::size_t> _recvBuf;
        std::pair<uint8_t *, std::size_t> _recvBuf{new uint8_t[_receivePacketSize], _receivePacketSize};
    };
} // namespace Network

#endif // BABEL_ANETWORK_HPP