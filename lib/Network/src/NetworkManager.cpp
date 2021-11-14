/*
** EPITECH PROJECT, 2021
** NetworkManager.cpp
** File description:
** TODO: add description
*/

#include "NetworkManager.hpp"
#include "Exceptions/NetworkException.hpp"

#include <utility>

NetworkManager::NetworkManager(std::shared_ptr<Network::IConnection<DataWrapper>> connector)
    : _connector(std::move(connector))
{
}

std::shared_ptr<Network::IConnection<DataWrapper>> NetworkManager::setConnector(
    std::shared_ptr<Network::IConnection<DataWrapper>> connector)
{
    auto tmp(std::move(_connector));

    _connector = std::move(connector);
    return tmp;
}

void NetworkManager::send(Tram::Serializable &data, const std::string &ip, const std::size_t port)
{
    if (!_connector->isConnected(ip, port)) {
        if (!_connector->connect(ip, port))
            throw Network::invalidConnection(Network::connectionFailed::_baseMessageFormat, ip, port);
    }
    _dataWrapper.deserialize(data.serialize(), data.length());
    _connector->send(_dataWrapper, ip, port);
}

std::tuple<uint8_t *, std::pair<std::string, std::size_t>> NetworkManager::receive()
{
    std::tuple<DataWrapper, std::size_t, std::string, std::size_t> receivedData(_connector->receiveAny());
    auto sender(std::make_pair(std::get<2>(receivedData), std::get<3>(receivedData)));

    if (_tramBuffers.find(sender) == _tramBuffers.end()) {
        _tramBuffers.emplace(sender, Tram::TramBuffer());
    }
    Tram::TramBuffer senderTramBuffer(_tramBuffers.at(sender));
    senderTramBuffer.SetData(
        std::get<0>(receivedData).serialize() /*todo ensure that this works*/, std::get<1>(receivedData));

    if (senderTramBuffer.isTramComplete())
        return std::make_tuple(senderTramBuffer.receiveTram(), sender);

    // if not full receive(ip, port)
    return std::make_tuple(nullptr, sender);
}