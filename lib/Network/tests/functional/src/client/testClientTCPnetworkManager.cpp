/*
** EPITECH PROJECT, 2021
** testClientTCPdataWrapper.cpp
** File description:
** test network TCP connection with data wrapper client side
*/

#include <cstring>
#include "AsioClientTCP.hpp"
#include "DataWrapper.hpp"
#include "NetworkManager.hpp"
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
int testClientConnectSendDisconnectNetworkManager()
{
    const std::string ipServer("127.0.0.1");
    const std::size_t portServer(8080);
    Tram::JoinRoom my_data{876};

    std::shared_ptr<IConnection<DataWrapper>> client(std::make_shared<AsioClientTCP<DataWrapper>>());

    NetworkManager clientManager(client);
    bool connected = clientManager.connect(ipServer, portServer);

    if (!connected)
        return 84;
    clientManager.sendAll(my_data);
    return 0;
}

int testClientConnectSendDisconnectNetworkManagerGetRoomList()
{
    const std::string ipServer("127.0.0.1");
    const std::size_t portServer(8080);
    std::vector<std::size_t> listOfRooms{222, 444};
    Tram::GetRoomList my_data{listOfRooms};

    std::shared_ptr<IConnection<DataWrapper>> client(std::make_shared<AsioClientTCP<DataWrapper>>());

    NetworkManager clientManager(client);
    bool connected = clientManager.connect(ipServer, portServer);

    if (!connected)
        return 84;
    clientManager.sendAll(my_data);
    return 0;
}