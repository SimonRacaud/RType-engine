/*
** EPITECH PROJECT, 2021
** testServerUDPdisconnection.cpp
** File description:
** test network UDP disconnection
*/

#include <cstring>
#include "AsioConnectionUDP.hpp"
#include "DataWrapper.hpp"
#include "NetworkManager.hpp"
#include "Tram/JoinRoom.hpp"
#include <unordered_map>

using namespace Network;

static const std::size_t portClient(8081);
static const std::string ipClient("127.0.0.1");
static const std::size_t portServer(8080);

static std::shared_ptr<IConnection<DataWrapper>> startServer()
{
    auto network(std::make_shared<AsioConnectionUDP<DataWrapper>>(portServer));

    return (network);
}

int testUDPserverDisconnection()
{
    auto network(startServer());

    while (!network->isConnected(ipClient, portClient)) {
        usleep(1);
    }
    while (network->isConnected(ipClient, portClient)) {
        usleep(1);
    }
    return 0;
}