/*
** EPITECH PROJECT, 2021
** NetworkManager.hpp
** File description:
** TODO: add description
*/
#ifndef R_TYPE_NETWORKMANAGER_HPP
#define R_TYPE_NETWORKMANAGER_HPP -

#include <queue>
#include "DataWrapper.hpp"
#include "INetwork.hpp"
#include "ISerializable.hpp"
#include "Tram/TramBuffer.hpp"
#include "utils/Concepts/Pointerable.hpp"

class NetworkManager {
  public:
    NetworkManager() = default;
    NetworkManager(const std::string &ip, const std::size_t port);
    ~NetworkManager() = default;
    void setConnector(std::shared_ptr<Network::IConnection<DataWrapper>> connector);

    void send(Network::ISerializable &data);
    Network::ISerializable &receive();

  private:
    Tram::TramBuffer _tramBuffer;
    std::shared_ptr<Network::IConnection<DataWrapper>> _network;

    std::queue<std::pair<Tram::TramType, Network::ISerializable>> _received;
    std::queue<std::pair<Tram::TramType, Network::ISerializable>> _toSend;
};

#endif // R_TYPE_NETWORKMANAGER_HPP