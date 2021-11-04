/*
** EPITECH PROJECT, 2021
** mainTestNetwork.cpp
** File description:
** TODO: add description
*/

#include <cstring>
#include "AsioClientTCP.hpp"
#include <unordered_map>

static const std::size_t PACKETSIZE = 123;

using namespace Network;

/**
 * @brief Test
 *  AsioClientTCP::connect()
 *  AsioClientTCP::send()
 *  AsioClientTCP::disconnect()
 * @return 0 if test succeeded
 */
int testClientConnectSendDisconnect()
{
    const std::string ipServer("127.0.0.1");
    const std::size_t portServer(8080);
    std::array<char, PACKETSIZE> sendBuf{"client connection, send, disconnection"};
    AsioClientTCP<PACKETSIZE> client;
    bool connected = client.connect(ipServer, portServer);

    if (!connected)
        return 84;
    client.send(sendBuf, ipServer, portServer);
    client.disconnect(ipServer, portServer);
    return 0;
}