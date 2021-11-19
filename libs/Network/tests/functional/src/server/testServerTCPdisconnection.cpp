/*
** EPITECH PROJECT, 2021
** testServerTCPdisconnection.cpp
** File description:
** test network TCP disconnection
*/

#include <cstring>
#include "AsioServerTCP.hpp"
#include "DataWrapper.hpp"
#include "Tram/JoinRoom.hpp"

using namespace Network;

static const std::size_t portServer(8080);

static std::shared_ptr<IConnection<DataWrapper>> startServer()
{
    auto network(std::make_shared<AsioServerTCP<DataWrapper>>(portServer));

    return (network);
}

int testTCPserverDisconnection()
{
    std::cout << __PRETTY_FUNCTION__ << std::endl;
    auto network(startServer());
    std::tuple<DataWrapper, std::size_t, std::string, std::size_t> dataReceived;
    std::string ipClient;
    std::size_t portClient(0);
    bool connection(false);

    while (true) {
        dataReceived = network->receiveAny();
        if (std::get<1>(dataReceived)) {
            ipClient = std::get<2>(dataReceived);
            portClient = std::get<3>(dataReceived);
            connection = network->isConnected(ipClient, portClient);
        }
        if (connection && !network->isConnected(ipClient, portClient)) {
            return 0;
        }
    }
    return 84;
}