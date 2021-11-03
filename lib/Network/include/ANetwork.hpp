/*
** EPITECH PROJECT, 2021
** ANetwork.hpp
** File description:
** Network Abstract class
*/
#ifndef BABEL_ANETWORK_HPP
#define BABEL_ANETWORK_HPP

#include <functional>
#include <thread>
#include "INetwork.hpp"
#include "utils/ThreadSafety/LockedDeque.hpp"
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
    template <std::size_t PACKETSIZE> class AAsioConnection : public IConnection<PACKETSIZE> {
      public:
        explicit AAsioConnection(const bool server = false) : _server(server)
        {
            runAsync();
        }

        ~AAsioConnection()
        {
            std::cout << "Stopping run async" << std::endl;
            stopRunAsync(); // todo search blocking / infinite loop
            std::cout << "Stopped run async" << std::endl;
            disconnectAll();
            std::cout << "Disconnect all" << std::endl;
        }

        AAsioConnection &operator=(const AAsioConnection<PACKETSIZE> &) = delete;
        AAsioConnection(const AAsioConnection<PACKETSIZE> &) = delete;

        bool connect(const std::string &ip, const std::size_t port) override
        {
            AAsioConnection<PACKETSIZE>::_connections.emplace_back(ip, port);
            return true;
        }

        // TODO ensure that base functions are called by inherited classes
        void disconnect(const std::string &ip, const std::size_t port) override
        {
            auto first(_connections.begin());
            auto last(_connections.end());
            std::pair<const std::string, const std::size_t> value(ip, port);

            first = std::find(first, last, value);

            //            if (first == last)
            //                throw Network::invalidConnection(Network::invalidConnection::_baseMessageFormat, ip,
            //                port);

            for (auto i = first; ++i != last;)
                if (!(*i == value))
                    (void) std::move(*i); // todo test
        }

        void disconnectAll() override
        {
            AAsioConnection<PACKETSIZE>::_connections.clear();
        }

        std::tuple<std::array<char, PACKETSIZE>, std::size_t, std::string, std::size_t> receiveAny() override = 0;

        std::pair<std::array<char, PACKETSIZE>, std::size_t> receive(
            const std::string &ip, const std::size_t port) override = 0;

        void sendAll(const std::array<char, PACKETSIZE> &buf) override = 0;

        void send(const std::array<char, PACKETSIZE> &buf, const std::string &ip, const std::size_t port) override = 0;

        [[nodiscard]] bool isConnected(const std::string &ip, const std::size_t port) const override
        {
            if (!AAsioConnection<PACKETSIZE>::_connections.empty()
                && std::find_if(_connections.begin(), _connections.end(),
                       [=](const auto &connection) {
                           return ip == connection.first && port == connection.second;
                       })
                    != AAsioConnection<PACKETSIZE>::_connections.end())
                return true;
            return false;
        }

        // Asynchronous operations

      private:
        /**
         * @brief Create a thread, which will execute asynchronous actions on
         *  network (accept connections and receive data)
         */
        void runAsync()
        {
            if (_thread.joinable())
                return;
            _thread = std::thread(&AAsioConnection<PACKETSIZE>::realRunAsync, this);
        }

        /**
         * @brief loop through awaiting asynchronous actions and stop if one is
         *  done to be called every time a connection or data is to be received
         */
        void realRunAsync()
        {
            while (_thread.joinable() && !AAsioConnection<PACKETSIZE>::_ioContext.stopped()) {
                std::cout << "thread running" << std::endl;
                _ioContext.run_one();
                usleep(500); // todo remove
            }
        }

        void stopRunAsync()
        {
            if (!_thread.joinable()) {
                return;
            }
            std::cout << "trying to stop io_context " << std::endl;
            if (!AAsioConnection<PACKETSIZE>::_ioContext.stopped()) {
                AAsioConnection<PACKETSIZE>::_ioContext.stop();
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

        ThreadSafety::LockedDeque<std::pair<const std::string, const std::size_t>> _connections;

        // Asynchronous operations
        /**
         * @property Contain data received from connections through
         *  asynchronous operations
         * @note std::atomic ensures thread safety over this variable
         */
        //        std::unordered_multimap<std::pair<const std::string, const std::size_t>,
        //            std::pair<std::array<char, PACKETSIZE>, std::size_t>, hash_pair>
        //            _recvData;
        ThreadSafety::LockedUnorderedMultimap<std::pair<const std::string, const std::size_t>,
            std::pair<std::array<char, PACKETSIZE>, std::size_t>, hash_pair>
            _recvData;
        /**
         * @property Run asynchronous asio operations in a non-blocking way
         */
        std::thread _thread;
        std::mutex _mutex;
        /**
         * @note std::atomic ensures thread safety over this variable
         */ // todo make atomic
        std::array<char, PACKETSIZE> _recvBuf{0};
    };
} // namespace Network

#endif // BABEL_ANETWORK_HPP