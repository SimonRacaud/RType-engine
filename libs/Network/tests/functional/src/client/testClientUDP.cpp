/*
** EPITECH PROJECT, 2021
** mainTestNetwork.cpp
** File description:
** TODO: add description
*/

#include <cstring>
#include "AsioConnectionUDP.hpp"
#include "DataWrapper.hpp"
#include "clientTest.hpp"
#include "intWrapper.hpp"

using namespace Network;

/**
 * @brief Test
 *  AsioConnectionUDP::connect()
 *  AsioConnectionUDP::send()
 *  AsioConnectionUDP::disconnect()
 * @return 0 if test succeeded
 */
int testUDPclientConnectSendDisconnect()
{
    const std::size_t portClient(8081);
    const std::string ipServer("127.0.0.1");
    const std::size_t portServer(8080);
    intWrapper myData(888);

    AsioConnectionUDP<intWrapper> client(portClient);
    usleep(300000); // wait for the server to setup
    bool connected = client.connect(ipServer, portServer);

    if (!connected)
        return 84;
    client.send(myData, ipServer, portServer);
    usleep(300000); // wait for the server to receive
    client.disconnect(ipServer, portServer);

    return 0;
}