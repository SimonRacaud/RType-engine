/*
** EPITECH PROJECT, 2021
** NetworkManager.hpp
** File description:
** TODO: add description
*/
#ifndef R_TYPE_NETWORKMANAGER_HPP
#define R_TYPE_NETWORKMANAGER_HPP -

#include <queue>
#include <tuple>
#include "DataWrapper.hpp"
#include "INetwork.hpp"
#include "Tram/Serializable.hpp"
#include "Tram/TramBuffer.hpp"
#include "utils/Concepts/Pointerable.hpp"
#include <unordered_map>

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

class NetworkManager {
  public:
    NetworkManager() = default;
    explicit NetworkManager(std::shared_ptr<Network::IConnection<DataWrapper>> connector);
    ~NetworkManager() = default;

    /**
     * @brief Set the IConnection that will be used to send and receive through network
     * @param connector The connector to be used
     * @return The old connector, or nullptr if does not exist
     */
    std::shared_ptr<Network::IConnection<DataWrapper>> setConnector(
        std::shared_ptr<Network::IConnection<DataWrapper>> connector);

    void send(Tram::Serializable &data, const std::string &ip, std::size_t port);
    void sendAll(Tram::Serializable &data);

    /**
     * @brief Get data from the received data queue
     * @return The data raw data (to be converted to the good class with tramConverter class), the sender
     */
    [[nodiscard]] std::tuple<uint8_t *, std::pair<std::string, std::size_t>> receive();

  private:
    std::unordered_map<std::pair<std::string, std::size_t>, Tram::TramBuffer, hash_pair> _tramBuffers;
    DataWrapper _dataWrapper;
    std::shared_ptr<Network::IConnection<DataWrapper>> _connector;

    std::queue<std::tuple<uint8_t *, std::pair<std::string, std::size_t>>> _received;
    std::queue<std::tuple<Tram::Serializable, std::pair<std::string, std::size_t>>> _toSend;
};

#endif // R_TYPE_NETWORKMANAGER_HPP