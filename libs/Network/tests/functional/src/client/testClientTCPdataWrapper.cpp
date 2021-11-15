/*
** EPITECH PROJECT, 2021
** testClientTCPdataWrapper.cpp
** File description:
** test network TCP connection with data wrapper client side
*/

#include <cstring>
#include "AsioClientTCP.hpp"
#include "DataWrapper.hpp"
#include "Tram/JoinRoom.hpp"

using namespace Network;

/**
 * @brief Test
 *  AsioClientTCP::connect()
 *  AsioClientTCP::send()
 *  AsioClientTCP::disconnect()
 *  class DataWrapper
 * @return 0 if test succeeded
 */
int testClientConnectSendDisconnectDataWrapper()
{
    const std::string ipServer("127.0.0.1");
    const std::size_t portServer(8080);
    Tram::JoinRoom my_data{51};
    DataWrapper myDataWrapper(my_data.serialize(), my_data.length());

    AsioClientTCP<DataWrapper> client;
    bool connected = client.connect(ipServer, portServer);

    if (!connected)
        return 84;
    client.send(myDataWrapper, ipServer, portServer);
    client.disconnect(ipServer, portServer);
    return 0;
}

int testClientConnectSendDisconnectDataWrapper2()
{
    const std::string ipServer("127.0.0.1");
    const std::size_t portServer(8080);
    std::vector<std::size_t> listOfRooms{222, 444};
    Tram::GetRoomList my_data{listOfRooms};
    DataWrapper myDataWrapper(my_data.serialize(), my_data.length());

    AsioClientTCP<DataWrapper> client;
    bool connected = client.connect(ipServer, portServer);

    if (!connected)
        return 84;
    client.send(myDataWrapper, ipServer, portServer);
    client.disconnect(ipServer, portServer);
    return 0;
}

// todo test all Trams