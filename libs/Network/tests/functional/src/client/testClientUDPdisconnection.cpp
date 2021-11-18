/*
** EPITECH PROJECT, 2021
** testClientUDPdisconnection.cpp
** File description:
** test network UDP disconnection
*/

#include <cstring>
#include "AsioConnectionUDP.hpp"
#include "DataWrapper.hpp"
#include "NetworkManager.hpp"
#include "Tram/JoinRoom.hpp"

using namespace Network;

static const std::size_t portClient(8081);
static const std::string ipServer("127.0.0.1");
static const std::size_t portServer(8080);

static std::shared_ptr<IConnection<DataWrapper>> startClient()
{
    auto network(std::make_shared<AsioConnectionUDP<DataWrapper>>(portClient));
    NetworkManager manager(network);
    usleep(300000); // wait for the server to setup

    manager.connect(ipServer, portServer);
    //    manager.send(data, ipServer, portServer);
    return manager.setConnector(nullptr);
}

int testUDPclientDisconnection()
{
    auto network(startClient());

    if (!network->isConnected(ipServer, portServer)) {
        return 1;
    }

    network->disconnect(ipServer, portServer);
    if (network->isConnected(ipServer, portServer)) {
        return 84;
    }

    return 0;
}