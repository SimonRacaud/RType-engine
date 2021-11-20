/*
** EPITECH PROJECT, 2021
** testClientTCPdisconnection.cpp
** File description:
** test network TCP disconnection
*/

#include <cstring>
#include "AsioClientTCP.hpp"
#include "DataWrapper.hpp"
#include "NetworkManager.hpp"
#include "Tram/JoinRoom.hpp"

using namespace Network;

static const std::string ipServer("127.0.0.1");
static const std::size_t portServer(8080);

static std::shared_ptr<IConnection<DataWrapper>> startClient()
{
    auto network(std::make_shared<AsioClientTCP<DataWrapper>>());
    NetworkManager manager(network);
    usleep(300000); // wait for the server to setup
    Tram::JoinRoom data(123);

    manager.connect(ipServer, portServer);
    manager.send(data, ipServer, portServer);
    usleep(300000); // wait for the server to receive

    return manager.setConnector(nullptr);
}

int testTCPclientDisconnection()
{
    auto network(startClient());

    if (!network->isConnected(ipServer, portServer)) {
        return 1;
    }
    usleep(300000); // let the time to the server to process
    network->disconnect(ipServer, portServer);
    if (network->isConnected(ipServer, portServer)) {
        return 84;
    }

    return 0;
}