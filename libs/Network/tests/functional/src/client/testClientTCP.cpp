/*
** EPITECH PROJECT, 2021
** mainTestNetwork.cpp
** File description:
** TODO: add description
*/

#include <cstring>
#include "AsioClientTCP.hpp"
#include "DataWrapper.hpp"
#include "clientTest.hpp"

using namespace Network;

/**
 * @brief Test
 *  AsioClientTCP::connect()
 *  AsioClientTCP::send()
 *  AsioClientTCP::disconnect()
 * @return 0 if test succeeded
 */
int testTCPclientConnectSendDisconnect()
{
    const std::string ipServer("127.0.0.1");
    const std::size_t portServer(8080);
    intWrapperTCPclient myData(888);
    AsioClientTCP<intWrapperTCPclient> client;
    usleep(300000); // wait for the server to setup
    bool connected = client.connect(ipServer, portServer);

    if (!connected)
        return 84;
    client.send(myData, ipServer, portServer);
    client.disconnect(ipServer, portServer);
    return 0;
}