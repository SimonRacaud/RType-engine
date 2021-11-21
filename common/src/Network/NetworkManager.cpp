/*
** EPITECH PROJECT, 2021
** NetworkManager.cpp
** File description:
** TODO: add description
*/

#include "../../include/Network/NetworkManager.hpp"

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

std::tuple<uint8_t *, std::pair<std::string, std::size_t>> NetworkManager::receive()
{
    if (!_connector)
        throw std::logic_error("No connector in NetworkManager");

    std::tuple<DataWrapper, std::size_t, std::string, std::size_t> receivedPacket(_connector->receiveAny());
    std::pair<DataWrapper, std::size_t> receivedData(std::get<0>(receivedPacket), std::get<1>(receivedPacket));
    auto sender(std::make_pair(std::get<2>(receivedPacket), std::get<3>(receivedPacket)));

    if (!receivedData.second) {
        return std::make_tuple(nullptr, sender);
    }
    if (_tramBuffers.find(sender) == _tramBuffers.end()) {
        _tramBuffers.emplace(sender, Tram::TramBuffer());
    }
    Tram::TramBuffer senderTramBuffer(_tramBuffers.at(sender));

setDataBuffer:
    senderTramBuffer.SetData(receivedData.first.serialize() /*todo ensure that this works*/, receivedData.second);

    if (!_connector)
        throw std::logic_error("No connector in NetworkManager");
    if (!senderTramBuffer.isTramComplete()) {
        receivedData = _connector->receive(sender.first, sender.second);
        goto setDataBuffer;
        // todo infinite loop handling ??
    }
    return std::make_tuple(senderTramBuffer.receiveTram(), sender);
}
bool NetworkManager::connect(const std::string &ip, const std::size_t port)
{
    if (!_connector)
        throw std::logic_error("No connector in NetworkManager");
    return _connector->connect(ip, port);
}